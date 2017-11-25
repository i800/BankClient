#include "Client.h"
#include "../Protocol/Packet.h"
#include "../Protocol/Packets/ErrorPacket.h"
#include "../Protocol/Packets/GetAccountMoneyPacket.h"
#include "../Protocol/Packets/GetAccountMoneyResponsePacket.h"
#include "../Protocol/Packets/GetCardsPacket.h"
#include "../Protocol/Packets/GetCardsResponsePacket.h"
#include "../Protocol/Packets/GetPaymentsPacket.h"
#include "../Protocol/Packets/GetPaymentsResponsePacket.h"
#include "../Protocol/Packets/MakePaymentPacket.h"
#include "../Protocol/Packets/MakePaymentResponsePacket.h"
#include "../Protocol/Packets/UserAuthPacket.h"
#include "../Protocol/Packets/UserAuthResponsePacket.h"
#include <cassert>

Client::Client():
    _isPending(true),
    _connection(new QTcpSocket(this))
{
    // In case of failed connection.
    connect(_connection,
        QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
        this, &Client::reactOnDisruption);

    connect(_connection, SIGNAL(aboutToClose()), this, SLOT(closeAll()));

    connect(_connection, SIGNAL(disconnected()), this, SLOT(abortAll()));

#ifndef NDEBUG
    qDebug("Client created.");
#endif
}

Client::~Client()
{
    delete _connection;

#ifndef NDEBUG
    qDebug("Client deleted.");
#endif
}

void Client::start(const char* host, const unsigned short port)
{
    _connection->abort();
    _connection->connectToHost(host, port);
    if (_connection->isOpen())
    {
        _isPending = false;
    }
}

void Client::abortAll()
{
    _connection->close();
    emit error("Connection lost");
}

void Client::closeAll()
{
    exit(0);
}

bool Client::processError(const QByteArray& arr)
{
    return !Packet::isPacket(arr) || Packet::getPacketId(arr) == 0;
}

void Client::requestForAuth(quint64 cardNumber, QString pass)
{
    connect(_connection, SIGNAL(readyRead()), this, SLOT(reactAuthResponse()));

    _cardNumber = cardNumber;
    _connection->write(UserAuthPacket(cardNumber, pass).dump());
    _connection->flush();
}

void Client::requestForAccMoney()
{
    connect(_connection, SIGNAL(readyRead()), this, SLOT(reactAccMoneyResponse()));

    _connection->write(GetAccountMoneyPacket(_session, _cardNumber).dump());
    _connection->flush();
}

void Client::requestForCards()
{
    connect(_connection, SIGNAL(readyRead()), this, SLOT(reactCardsResponse()));
    // _cardNumber is not userId.
    _connection->write(GetCardsPacket(_session, _cardNumber).dump());
    _connection->flush();
}

void Client::requestForPayments()
{
    connect(_connection, SIGNAL(readyRead()), this, SLOT(reactCardsResponse()));

    _connection->write(GetPaymentsPacket(_session, _cardNumber).dump());
    _connection->flush();
}

void Client::reactAuthResponse()
{
    disconnect(_connection, SIGNAL(readyRead()), this, SLOT(reactAuthResponse()));

    QByteArray arr = _connection->readAll();
    if (!processError(arr))
    {
        UserAuthResponsePacket response;
        response.load(arr);
        _session = response.token();
        emit authPassed();
    }
    else
    {
        emit authFailed();
    }
}

void Client::reactAccMoneyResponse()
{
    disconnect(_connection, SIGNAL(readyRead()), this, SLOT(reactAccMoneyResponse()));

    QByteArray arr = _connection->readAll();
    if (!processError(arr))
    {
        GetAccountMoneyResponsePacket response;
        response.load(arr);
        emit gotAccountMoney(response.amount());
    }
    else
    {
        emit error("Cannot get account money, please, retry do this action later.");
    }
}

void Client::reactCardsResponse()
{
    disconnect(_connection, SIGNAL(readyRead()), this, SLOT(reactCardsResponse()));

    QByteArray arr = _connection->readAll();
    if (!processError(arr))
    {
        GetCardsResponsePacket response;
        response.load(arr);
        emit gotAccountCardsAmount(response.cards().size());
    }
    else
    {
        emit error("Cannot get account cards, please, retry do this action later.");
    }
}

void Client::reactPaymentsResponse()
{
    disconnect(_connection, SIGNAL(readyRead()), this, SLOT(reactPaymentsResponse()));

    QByteArray arr = _connection->readAll();
    if (!processError(arr))
    {
        GetPaymentsResponsePacket response;
        response.load(arr);
        emit gotPaymentsAmount(response.paymentsAmount()); // TODO response.getPayments()
    }
    else
    {
        emit error("Cannot get account cards, please, retry do this action later.");
    }
}

void Client::reactOnDisruption()
{
    emit disruption();

#ifndef NDEBUG
    qFatal("Connection disrupted.");
#endif
}
