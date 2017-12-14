#include "Client.h"
#include <cassert>

Client::Client():
    _isPending(true),
    _connection(new QTcpSocket(this)),
    _logout_send_when_close(1)
{
    configureClient(_configuration);

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

Client::Client(const ClientConfiguration& config):
    _isPending(true),
    _connection(new QTcpSocket(this)),
    _configuration(config)
{
    configureClient(_configuration);

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

void Client::start()
{
    _connection->abort();
    _connection->connectToHost(_host, _port);
    if (_connection->isOpen())
    {
        _isPending = false;
    }
}

void Client::configureClient(const ClientConfiguration& config)
{
    _host = config.address();
    _port = config.serverPort();
}

void Client::abortAll()
{
    _connection->close();
    emit error("Connection lost");
}

void Client::closeAll()
{
    if(_logout_send_when_close)
    {
        _logout_send_when_close=false;
        connect(_connection, SIGNAL(readyRead()), this, SLOT(reactSuccessLogout()));

        _connection->write(UserLogoutPacket(_session, _terminalId).dump());
        _connection->flush();
    }
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

void Client::requestForPeriodicalPayments(quint64 cardNumber)
{
    connect(_connection, SIGNAL(readyRead()), this, SLOT(reactPeriodicalPaymentsResponse()));

    GetPaymentsPacket packet(_session, _terminalId, cardNumber);
    packet.setPaymentsType(GetPaymentsPacket::PERIODIC_PAYMENTS);
    _connection->write(packet.dump());
    _connection->flush();
}

void Client::requestForTransaction(quint64 from, quint64 to, quint64 amount, quint64 time, QString& comment)
{
    connect(_connection, SIGNAL(readyRead()), this, SLOT(reactTransactionResponse()));

    _connection->write(MakePaymentPacket(_session, from, qint64(to), qint64(amount), _terminalId, time, comment, comment).dump());
    _connection->flush();
}

void Client::requestForPCancelling(quint64 id)
{
    qDebug("requestForPCancelling");
    connect(_connection, SIGNAL(readyRead()), this, SLOT(reactPCancellingResponse()));

    _connection->write(CancelPeriodicPaymentPacket(_session, _terminalId, id).dump());
    _connection->flush();
    qDebug("end requestForPCancelling");
}

QByteArray Client::readPacket()
{
    QByteArray result = _connection->readAll();
    while(!Packet::isPacket(result))
    {
        _connection->waitForReadyRead();
        result.append(_connection->readAll());
    }
    return result;
}

void Client::reactAuthResponse()
{
    QByteArray arr = readPacket();
    disconnect(_connection, SIGNAL(readyRead()), this, SLOT(reactAuthResponse()));
    if(Packet::getPacketId(arr) != 0)
    {
        UserAuthResponsePacket response;
        response.load(arr);
        _session = response.token();
        emit authPassed();
    }
    else
    {
        ErrorPacket pack;
        pack.load(arr);
        emit authFailed();
    }
}

void Client::reactAccMoneyResponse()
{
    QByteArray arr = readPacket();
    disconnect(_connection, SIGNAL(readyRead()), this, SLOT(reactAccMoneyResponse()));
    if(Packet::getPacketId(arr) != 0)
    {
        GetAccountMoneyResponsePacket response;
        response.load(arr);
        qDebug(QString::number(response.amount()).toStdString().c_str());
        emit gotAccountMoney(response.amount());
    }
    else
    {
        ErrorPacket pack;
        pack.load(arr);
        emit error(pack.info());
    }
}

void Client::reactCardsResponse()
{
    QByteArray arr = readPacket();
    disconnect(_connection, SIGNAL(readyRead()), this, SLOT(reactCardsResponse()));
    if(Packet::getPacketId(arr) != 0)
    {
        GetCardsResponsePacket response;
        response.load(arr);
        emit gotAccountCards(response.cards());
    }
    else
    {
        ErrorPacket pack;
        pack.load(arr);
        emit authFailed();
    }
}

void Client::reactPaymentsResponse()
{
    QByteArray arr = readPacket();
    disconnect(_connection, SIGNAL(readyRead()), this, SLOT(reactPaymentsResponse()));
    if(Packet::getPacketId(arr) != 0)
    {
        GetPaymentsResponsePacket response;
        response.load(arr);
        QMap<quint64, QPair<quint64, quint64>> payments(convertToMap(response));
        emit gotPayments(payments);
    }
    else
    {
        ErrorPacket pack;
        pack.load(arr);
        emit error(pack.info());
        //emit authFailed();
    }
}

void Client::reactPeriodicalPaymentsResponse()
{
    QByteArray arr = readPacket();
    disconnect(_connection, SIGNAL(readyRead()), this, SLOT(reactPeriodicalPaymentsResponse()));
    if(Packet::getPacketId(arr) != 0)
    {
        GetPaymentsResponsePacket response;
        response.load(arr);
        QMap<quint64, QPair<quint64, quint64>> payments(convertToMap(response));
        emit gotPeriodicalPayments(payments);
    }
    else
    {
        ErrorPacket pack;
        pack.load(arr);
        emit error(pack.info());
        //emit authFailed();
    }
}

void Client::reactTransactionResponse()
{
    QByteArray arr = readPacket();
    disconnect(_connection, SIGNAL(readyRead()), this, SLOT(reactTransactionResponse()));
    if(Packet::getPacketId(arr) != 0)
    {
        MakePaymentResponsePacket response;
        response.load(arr);
        MakePaymentResponsePacket::PaymentStatus status = response.getPaymentStatus();
        emit gotTransactionSuccess(status);
    }
    else
    {
        ErrorPacket pack;
        pack.load(arr);
        emit error(pack.info());
        //emit error("Cannot make a transaction, please, retry do this action later.");
    }
}

void Client::reactPCancellingResponse()
{
    QByteArray arr = readPacket();
    disconnect(_connection, SIGNAL(readyRead()), this, SLOT(reactPCancellingResponse()));
    if(Packet::getPacketId(arr) != 0)
    {
        emit gotPCancellingSuccess();
    }
    else
    {
        ErrorPacket pack;
        pack.load(arr);
        emit error(pack.info());
        //emit error("Cannot make a transaction, please, retry do this action later.");
    }
}

void Client::reactOnDisruption()
{
    emit disruption();

#ifndef NDEBUG
    qFatal("Connection disrupted.");
#endif
}

void Client::reactSuccessLogout()
{
    disconnect(_connection, SIGNAL(readyRead()), this, SLOT(reactSuccessLogout()));

#ifndef NDEBUG
    qDebug("Correct exit.");
#endif
//    _connection->close();
    exit(0);
}

QMap<quint64, QPair<quint64, quint64>> convertToMap(const GetPaymentsResponsePacket& packet)
{
    QMap<quint64, QPair<quint64, quint64>> data;
    quint16 amount(packet.paymentsAmount());
    for (quint16 i(0); i < amount; ++i)
    {
        data.insert(packet.paymentId(i),
                    QPair<quint64, quint64>(packet.to(i), packet.amount(i)));
    }

    return data;
}
