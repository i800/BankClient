#include "Client.h"
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
    _connection->write(UserLogoutPacket(_session, _terminalId).dump());
    exit(0);
}

bool Client::processError(const QByteArray& arr)
{
    return !Packet::isPacket(arr) || Packet::getPacketId(arr) == 0;
}

quint32 Client::getTerminalId()
{
    int a(0);
    int b(0);

    __asm__("cpuid;"
            :"=a"(b)
            :"0"(a)
            :"%ebx","%ecx","%edx");

    return quint32(b);
}

void Client::requestForAuth(quint64 cardNumber, QString pass)
{
    connect(_connection, SIGNAL(readyRead()), this, SLOT(reactAuthResponse()));

    _cardNumber = cardNumber;
    _connection->write(UserAuthPacket(cardNumber, pass, _terminalId).dump());
    _connection->flush();
}

void Client::requestForAccMoney(quint64 cardNumber)
{
    connect(_connection, SIGNAL(readyRead()), this, SLOT(reactAccMoneyResponse()));

    qDebug(QString::number(cardNumber).toStdString().c_str());
    _connection->write(GetAccountMoneyPacket(_session, _terminalId, cardNumber).dump());
    _connection->flush();
}

void Client::requestForCards()
{
    connect(_connection, SIGNAL(readyRead()), this, SLOT(reactCardsResponse()));
    // _cardNumber is not userId.
    _connection->write(GetCardsPacket(_session, _terminalId, _cardNumber).dump());
    _connection->flush();
}

void Client::requestForPayments(quint64 cardNumber)
{
    connect(_connection, SIGNAL(readyRead()), this, SLOT(reactPaymentsResponse()));

    _connection->write(GetPaymentsPacket(_session, _terminalId, cardNumber).dump());
    _connection->flush();
}

void Client::requestForTransaction(quint64 from, quint64 to, quint64 amount, quint64 time, QString& comment)
{
    connect(_connection, SIGNAL(readyRead()), this, SLOT(reactTransactionResponse()));

    _connection->write(MakePaymentPacket(_session, from, qint64(to), qint64(amount), _terminalId, time, comment, comment).dump());
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
        qDebug(QString::number(response.amount()).toStdString().c_str());
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
        emit gotAccountCards(response.cards());
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
        emit error("Cannot get payments, please, retry do this action later.");
    }
}

void Client::reactTransactionResponse()
{
    disconnect(_connection, SIGNAL(readyRead()), this, SLOT(reactTransactionResponse()));

    QByteArray arr = _connection->readAll();
    if (!processError(arr))
    {
        MakePaymentResponsePacket response;
        response.load(arr);
        MakePaymentResponsePacket::PaymentStatus status = response.getPaymentStatus();
        emit gotTransactionSuccess(status);
    }
    else
    {
        emit error("Cannot make a transaction, please, retry do this action later.");
    }
}

void Client::reactOnDisruption()
{
    emit disruption();

#ifndef NDEBUG
    qFatal("Connection disrupted.");
#endif
}
