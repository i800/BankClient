#include "App.h"
#include "Protocol/Packet.h"

App::App(QObject *parent):
    QObject(parent)
{
    _client.start();
    _authFrame.show();

    connect(&_authFrame, SIGNAL(callForAuth(long long, short)),
            &_client, SLOT(requestForAuth(long long, short)));

    connect(&_client, SIGNAL(authFailed()), &_authFrame, SLOT(reactAuthFailed()));

    connect(&_client, SIGNAL(authPassed()), this, SLOT(reactAuthPassed()));

#ifndef NDEBUG
    qDebug("App created.");
#endif
}

void App::reactAuthPassed()
{
    _authFrame.close();
    _mainWindow.show();
}
