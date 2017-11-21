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
    QTcpSocket* _connection;
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;
    bool processError(const QByteArray&);
public:
    explicit Client();
    ~Client();
    void start(const char* host = "localhost",
               const unsigned short port = 45654);
private slots:
    /**
     * Requests to the server.
     * Each request from the client
     * has a prefix 'request'.
     */
    void requestForAuth(quint64 cardNumber, QString pass);
    void requestForAccMoney();
    void requestForCards();
    void requestForPayments();
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
    void gotAccountCardsAmount(uint);
    void gotPaymentsAmount(uint);
    void error(QString);
};

#endif // CLIENT_H
