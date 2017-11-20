#include "App.h"
#include "Protocol/Packet.h"

App::App(QObject *parent):
    QObject(parent)
{
    _client.start();
    _authFrame.show();

    connect(&_authFrame, SIGNAL(callForAuth(long long, QString)),
            &_client, SLOT(requestForAuth(long long, QString)));

    connect(&_client, SIGNAL(authFailed()), &_authFrame, SLOT(reactAuthFailed()));

    connect(&_client, SIGNAL(authPassed()), this, SLOT(reactAuthPassed()));

    connect(&_client, SIGNAL(error(QString)), &_mainWindow, SLOT(reactError(QString)));

#ifndef NDEBUG
    qDebug("App created.");
#endif
}

void App::reactAuthPassed()
{
    _authFrame.close();
    _mainWindow.show();
}
