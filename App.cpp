#include "App.h"
#include "Protocol/Packet.h"
#include <QMessageBox>

App::App(QObject *parent):
    QObject(parent)
{
    _client.start();//("217.147.175.29", 21025);//"platinium.ddns.net");
    _authFrame.show();

    connect(&_authFrame, SIGNAL(callForAuth(quint64, QString)),
            &_client, SLOT(requestForAuth(quint64, QString)));

    connect(&_mainWindow, SIGNAL(callForAccMoney(quint64)),
            &_client, SLOT(requestForAccMoney(quint64)));

    connect(&_mainWindow, SIGNAL(callForAccCards()),
            &_client, SLOT(requestForCards()));

    connect(&_mainWindow, SIGNAL(callForPayments(quint64)),
            &_client, SLOT(requestForPayments(quint64)));

    connect(&_mainWindow, SIGNAL(callForTransaction()),
            this, SLOT(requestForTransaction()));

    connect(&_mainWindow, SIGNAL(callForTransactionDone(quint64 from, quint64 to, quint64 amount,QString& comment)),
            &_client, SLOT(requestForTransaction(quint64 from, quint64 to, quint64 amount, QString& comment)));

    connect(&_transactionFrame, SIGNAL(callForClose()),
            this, SLOT(reactOnTransactionFrameClose()));

    connect(&_transactionFrame, SIGNAL(callForTransaction(quint64 to, quint64 amount, QString& comment)),
            &_mainWindow, SLOT(requestForTransactionDone(quint64 to, quint64 amount, QString& comment)));

    connect(&_client, SIGNAL(disruption()), this, SLOT(reactDisruption()));

    connect(&_client, SIGNAL(authFailed()), &_authFrame, SLOT(reactAuthFailed()));

    connect(&_client, SIGNAL(authPassed()), this, SLOT(reactAuthPassed()));

    connect(&_client, SIGNAL(error(QString)),
            &_mainWindow, SLOT(reactError(QString)));

    connect(&_client, SIGNAL(gotAccountMoney(quint64)),
            &_mainWindow, SLOT(reactGotAccMoney(quint64)));

    connect(&_client, SIGNAL(gotAccountCards(QMap<quint64, quint8>&)),
            &_mainWindow, SLOT(reactGotAccCards(QMap<quint64, quint8>&)));

    connect(&_client, SIGNAL(gotPaymentsAmount(uint)),
            &_mainWindow, SLOT(reactGotPaymentsAmount(uint)));

#ifndef NDEBUG
    qDebug("App created.");
#endif
}

void App::requestForTransaction()
{
    _transactionFrame.show();
    if (_transactionFrame.firstInit())
    {
        QList<QString> temp(_mainWindow.cardsList());
        _transactionFrame.setCards(temp);
    }
}

void App::reactAuthPassed()
{
    _authFrame.close();
    _mainWindow.show();
    _mainWindow.setLoggedInCard(_client.cardNumber());
    _mainWindow.requestForCards();
    //_client.requestForAccMoney(_client.cardNumber());
    //_client.requestForPayments(_client.cardNumber());
}

void App::reactDisruption()
{
    _authFrame.close();
    _mainWindow.close();
    QMessageBox::information(0, "Error", "Sorry, connection with server lost");
    exit(0);
}

void App::reactOnTransactionFrameClose()
{
    _mainWindow.setWaitingMode(false);
}
