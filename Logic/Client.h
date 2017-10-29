#ifndef CLIENT_H
#define CLIENT_H
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
private:
    bool _isPending;
    QTcpSocket* _connection;
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;
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
    void requestForAuth(long long, short);
    // Other requests (...)

    /**
     * Reactions for the server responses.
     * Each reaction has a prefix 'react'.
     */
    void reactAuthResponse();
    void reactOnDisruption();
    // Other reactions (...)
signals:
    void disruption();
    void authPassed();
    void authFailed();
};

#endif // CLIENT_H
