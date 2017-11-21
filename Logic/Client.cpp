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
    qFatal("bhbhbjbjhb");
    emit error("Connection lost");
}

bool Client::processError(const QByteArray& arr)
{
    return !Packet::isPacket(arr) || Packet::getPacketId(arr) == 0;
}

void Client::requestForAuth(long long cardnum, QString pass)
{
    connect(_connection, SIGNAL(readyRead()), this, SLOT(reactAuthResponse()));

    _connection->write(UserAuthPacket(cardnum, pass).dump());
    _connection->flush();
}

void Client::requestForAccMoney(quint64 token, quint64 accountId)
{
    connect(_connection, SIGNAL(readyRead()), this, SLOT(reactAccMoneyResponse()));

    _connection->write(GetAccountMoneyPacket(token, accountId).dump());
    _connection->flush();
}

void Client::requestForCards(quint64 token, quint64 userId)
{
    connect(_connection, SIGNAL(readyRead()), this, SLOT(reactCardsResponse()));

    _connection->write(GetCardsPacket(token, userId).dump());
    _connection->flush();
}

void Client::requestForPayments(quint64 token, quint64 cardNumber)
{
    connect(_connection, SIGNAL(readyRead()), this, SLOT(reactCardsResponse()));

    _connection->write(GetPaymentsPacket(token, cardNumber).dump());
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
        emit error("Login failed. Check your input or try later.");
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
