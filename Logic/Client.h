#ifndef CLIENT_H
#define CLIENT_H
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
private:
    bool _isPending;
    QString _session;
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
    void requestForAuth(long long, QString);
    void requestForAccMoney(quint64, quint64);
    void requestForCards(quint64, quint64);
    void requestForPayments(quint64, quint64);
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
signals:
    void disruption();
    void authPassed();
    void authFailed();
    void gotAccountMoney(quint64);
    void gotAccountCards(QMap<quint64, quint8>);
    void gotPayments(QByteArray);
    void error(QString);
};

#endif // CLIENT_H
