#ifndef CONSOLEUI_H
#define CONSOLEUI_H
#include "../Client/Client.h"

class ConsoleApp
{
private:
    mutable Client _client;
    ConsoleApp(const ConsoleApp&) = delete;
    ConsoleApp& operator=(const ConsoleApp&) = delete;
    void sendAuthPacket() const;
    void showInfo() const;
public:
    ConsoleApp();
    ~ConsoleApp();
    void start();
};

#endif // CONSOLEUI_H
