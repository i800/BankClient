#include "ConsoleApp.h"
#include "../Protocol/Client/UserAuthPacket.h"
#include <iostream>

ConsoleApp::ConsoleApp()
{
    _client.start();
#ifndef NDEBUG
    qDebug("Console debug application created.");
#endif
}

ConsoleApp::~ConsoleApp()
{
#ifndef NDEBUG
    qDebug("Console debug application closed.");
#endif
}

void ConsoleApp::start()
{
    while(true)
    {
        qInfo("App menu. Please, choose an action:");
        qInfo("0 - shutdown;");
        qInfo("1 - output Qt version;");
        qInfo("2 - send a packet to the server*.");
        qInfo("*Note that the server must be turned on.");

        qInfo("Your choice: ");
        int choice(-1);
        std::cin >> choice;
        switch (choice) {
        case 0:
            return;
        case 1:
            showInfo();
            break;
        default:
            break;
        }
    }
}

void ConsoleApp::sendAuthPacket() const
{
    _client.sendPacket(Protocol::UserAuthPacket());
}

void ConsoleApp::showInfo() const
{
    qInfo() << qVersion();
}
