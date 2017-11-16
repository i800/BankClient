#include "Client.h"
#include "../Protocol/Packet.h"
#include "../Protocol/Packets/UserAuthPacket.h"
#include "../Protocol/Packets/MakePaymentPacket.h"
#include "../Protocol/Packets/MakePaymentResponsePacket.h"
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

void Client::requestForAuth(long long cardnum, short pass)
{
    connect(_connection, SIGNAL(readyRead()), this, SLOT(reactAuthResponse()));

    _connection->write(UserAuthPacket(cardnum, pass).dump());
    _connection->flush();
}

void Client::reactAuthResponse()
{
    disconnect(_connection, SIGNAL(readyRead()), this, SLOT(reactAuthResponse()));

    QByteArray arr = _connection->readAll();
#if 0
    if (!Packet::isPacket(arr) || Packet::getPacketId(arr) != 1)
    {
        emit authFailed();
    }
    else
    {
        emit authPassed();
    }
#endif
#if 1
    emit authPassed();
#endif
}

void Client::reactOnDisruption()
{
    emit disruption();

#ifndef NDEBUG
    qFatal("Connection disrupted.");
#endif
}
