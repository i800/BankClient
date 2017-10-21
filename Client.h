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
    // For testing.
    void ping();
private slots:
    void readResponse();
    void displayError();
};

#endif // CLIENT_H
