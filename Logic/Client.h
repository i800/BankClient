#ifndef CLIENT_H
#define CLIENT_H
#include <QTcpSocket>
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
#include "../Protocol/Packets/UserLogoutPacket.h"
#include "../Protocol/Packets/CancelPeriodicPaymentPacket.h"
#include "ClientConfiguration.h"

class Client : public QObject
{
    Q_OBJECT
private:
    bool _isPending;
    quint64 _session;
    quint64 _cardNumber;
    quint32 _terminalId;
    QTcpSocket* _connection;
    ClientConfiguration _configuration;
    QString _host;
    unsigned short _port;
    bool _logout_send_when_close;
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;
    bool processError(const QByteArray&);
    quint32 getTerminalId();
    QByteArray readPacket();
public:
    explicit Client();
    Client(const ClientConfiguration&);
    ~Client();
    void start();
    void configureClient(const ClientConfiguration&);
    quint64 cardNumber() const { return _cardNumber; }

    quint32 terminalId() const
    {
        return _terminalId;
    }

public slots:
    /**
     * Requests to the server.
     * Each request from the client
     * has a prefix 'request'.
     */
    void requestForAuth(quint64 cardNumber, QString pass);
    void requestForAccMoney(quint64);
    void requestForCards();
    void requestForPayments(quint64);
    void requestForPeriodicalPayments(quint64);
    void requestForTransaction(quint64 from, quint64 to, quint64 amount,
                               quint64 time, QString& comment);
    void requestForPCancelling(quint64);

    /**
     * Reactions for the server responses.
     * Each reaction has a prefix 'react'.
     */
    void reactAuthResponse();
    void reactAccMoneyResponse();
    void reactCardsResponse();
    void reactPaymentsResponse();
    void reactPeriodicalPaymentsResponse();
    void reactTransactionResponse();
    void reactPCancellingResponse();
    void reactOnDisruption();
//    DD
    void reactSuccessLogout();

    void abortAll();
    void closeAll();
signals:
    void disruption();
    void authPassed();
    void authFailed();
    void gotAccountMoney(quint64);
    void gotAccountCards(QMap<quint64, quint8>&);
    void gotAccountCardsAmount(uint);
    void gotPayments(QMap<quint64, QPair<quint64, quint64>>&);
    void gotPeriodicalPayments(QMap<quint64, QPair<quint64, quint64>>&);
    void gotTransactionSuccess(MakePaymentResponsePacket::PaymentStatus&);
    void gotPCancellingSuccess();
    void error(QString);
};

QMap<quint64, QPair<quint64, quint64>> convertToMap(const GetPaymentsResponsePacket&);

#endif // CLIENT_H
