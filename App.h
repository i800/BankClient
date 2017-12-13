#ifndef APP_H
#define APP_H

#include "Logic/Client.h"
#include "GUI/AuthFrame.h"
#include "GUI/MainWindow.h"
#include "GUI/TransactionFrame.h"
#include "GUI/PCancellingFrame.h"
#include <QObject>

class App : public QObject
{
    Q_OBJECT
private:
    // Logic.
    Client _client;
    // GUI.
    AuthFrame _authFrame;
    MainWindow _mainWindow;
    TransactionFrame _transactionFrame;
    PCancellingFrame _pCancellingFrame;
    // Deleted class members.
    App(const App&) = delete;
    App& operator=(const App&) = delete;
public:
    explicit App(QObject *parent = nullptr);

public slots:
    /**
     * Requests to the client.
     * Each request to the client
     * has a prefix 'request'.
     */
    void requestForTransaction();
    void requestForPCancelling();

    /** Reactions.
     * Each reaction has a prefix 'react'.
     */
    void reactAuthPassed();
    void reactDisruption();
    void reactOnTransactionFrameClose();
};

#endif // APP_H
