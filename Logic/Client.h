#ifndef CLIENT_H
#define CLIENT_H
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
private:
    bool _isPending;
    quint64 _session;
    quint64 _cardNumber;
    quint32 _terminalId;
    QTcpSocket* _connection;
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;
    bool processError(const QByteArray&);
    quint32 getTerminalId();
public:
    explicit Client();
    ~Client();
    void start(const char* host = "localhost",
               const unsigned short port = 45654);
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
    // Other requests (...)

    /**
     * Reactions for the server responses.
     * Each reaction has a prefix 'react'.
     */
    void reactAuthResponse();
    void reactAccMoneyResponse();
    void reactCardsResponse();
    void reactPaymentsResponse();
    void reactOnDisruption();

    void abortAll();
    void closeAll();
signals:
    void disruption();
    void authPassed();
    void authFailed();
    void gotAccountMoney(quint64);
    void gotAccountCards(QMap<quint64, quint8>&);
    void gotAccountCardsAmount(uint);
    void gotPaymentsAmount(uint);
    void error(QString);
};

#endif // CLIENT_H
