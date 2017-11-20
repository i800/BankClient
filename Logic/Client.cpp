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

void Client::requestForAuth(long long cardnum, QString pass)
{
    connect(_connection, SIGNAL(readyRead()), this, SLOT(reactAuthResponse()));

    _connection->write(UserAuthPacket(cardnum, pass).dump());
    _connection->flush();
}

void Client::reactAuthResponse()
{
    disconnect(_connection, SIGNAL(readyRead()), this, SLOT(reactAuthResponse()));

    QByteArray arr = _connection->readAll();
    if (!Packet::isPacket(arr) || Packet::getPacketId(arr) != -1)
    {
        emit authFailed();
    }
    else
    {
        UserAuthResponsePacket response;
        response.load(arr);
        _session = response.token();
        emit authPassed();
    }
}

void Client::reactOnDisruption()
{
    emit disruption();

#ifndef NDEBUG
    qFatal("Connection disrupted.");
#endif
}
