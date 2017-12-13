#include "App.h"
#include "Protocol/Packet.h"
#include <QMessageBox>

App::App(QObject *parent):
    QObject(parent)
{
    _client.start("127.0.0.1", 45654);//"platinium.ddns.net", 21025); //"217.147.175.29";
    _authFrame.show();

    connect(&_authFrame, SIGNAL(callForAuth(quint64, QString)),
            &_client, SLOT(requestForAuth(quint64, QString)));

    connect(&_mainWindow, SIGNAL(callForAccMoney(quint64)),
            &_client, SLOT(requestForAccMoney(quint64)));

    connect(&_mainWindow, SIGNAL(callForPeriodicalPaymentsIds(quint64)),
            &_client, SLOT(requestForPeriodicalPayments(quint64)));

    connect(&_mainWindow, SIGNAL(callForAccCards()),
            &_client, SLOT(requestForCards()));

    connect(&_mainWindow, SIGNAL(callForPayments(quint64)),
            &_client, SLOT(requestForPayments(quint64)));

    connect(&_mainWindow, SIGNAL(callForTransaction()),
            this, SLOT(requestForTransaction()));

    connect(&_mainWindow, SIGNAL(callForPCancelling()),
            this, SLOT(requestForPCancelling()));

    connect(&_mainWindow, SIGNAL(callForTransactionDone(quint64, quint64, quint64, quint64, QString&)),
            &_client, SLOT(requestForTransaction(quint64, quint64, quint64, quint64, QString&)));

    connect(&_mainWindow, SIGNAL(callForCancellingDone(quint64)),
            &_client, SLOT(requestForPCancelling(quint64)));

    connect(&_mainWindow, SIGNAL(callForQuit()),
            &_client, SLOT(closeAll()));

    connect(&_transactionFrame, SIGNAL(callForClose()),
            this, SLOT(reactOnTransactionFrameClose()));

    connect(&_transactionFrame, SIGNAL(callForTransaction(quint64, quint64, quint64, QString&)),
            &_mainWindow, SLOT(requestForTransactionDone(quint64, quint64, quint64, QString&)));

    connect(&_pCancellingFrame, SIGNAL(callForIds()),
            &_mainWindow, SLOT(requestForPeriodicalPaymentsIds()));

    connect(&_pCancellingFrame, SIGNAL(callForClose()),
            this, SLOT(reactOnTransactionFrameClose()));

    connect(&_pCancellingFrame, SIGNAL(callForPCancelling(quint64)),
            &_mainWindow, SLOT(requestForCancellingDone(quint64)));

    connect(&_client, SIGNAL(disruption()), this, SLOT(reactDisruption()));

    connect(&_client, SIGNAL(authFailed()), &_authFrame, SLOT(reactAuthFailed()));

    connect(&_client, SIGNAL(authPassed()), this, SLOT(reactAuthPassed()));

    connect(&_client, SIGNAL(error(QString)),
            &_mainWindow, SLOT(reactError(QString)));

    connect(&_client, SIGNAL(gotAccountMoney(quint64)),
            &_mainWindow, SLOT(reactGotAccMoney(quint64)));

    connect(&_client, SIGNAL(gotAccountCards(QMap<quint64, quint8>&)),
            &_mainWindow, SLOT(reactGotAccCards(QMap<quint64, quint8>&)));

    connect(&_client, SIGNAL(gotPayments(QMap<quint64, QPair<quint64, quint64>>&)),
            &_mainWindow, SLOT(reactGotPayments(QMap<quint64, QPair<quint64, quint64>>&)));

    connect(&_client, SIGNAL(gotPeriodicalPayments(QMap<quint64,QPair<quint64,quint64>>&)),
            &_pCancellingFrame, SLOT(setIds(QMap<quint64,QPair<quint64,quint64>>&)));

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

void App::requestForPCancelling()
{
    _pCancellingFrame.show();
    _pCancellingFrame.setIds();
}

void App::reactAuthPassed()
{
    _authFrame.close();
    _mainWindow.show();
    _mainWindow.setLoggedInCard(_client.cardNumber());
    _mainWindow.requestForCards();
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
