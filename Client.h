#ifndef CLIENT_H
#define CLIENT_H
#include <QtNetwork/QTcpSocket>

class Client : QObject
{
    Q_OBJECT
private:
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;
public:
    explicit Client();
    ~Client();
    void start(const char* host = "localhost",
               const unsigned short port = 45654);
    // For testing.
    void ping();
private slots:
    void serverConnected();
};

#endif // CLIENT_H
