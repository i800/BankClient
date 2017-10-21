#include "Client.h"
#include <cassert>

Client::Client():
    _isPending(true),
    _connection(new QTcpSocket(this))
{
    connect(_connection,
            QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, Client::displayError());
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
    _connection->abort(); // To avoid troubles with async.
    _connection->connectToHost(host, port);
    if (_connection->isOpen())
    {
        _isPending = false;
    }
}

void Client::ping()
{
    assert(!_isPending);
    _connection->write("Ping, Andrew!!! P.S. I know this is not a packet.");
}

void Client::readResponse()
{
    QByteArray arr = _connection->readAll();
    qDebug(QString(arr));
}

void Client::displayError()
{
    qFatal("Cannot connect to the server!");
}
