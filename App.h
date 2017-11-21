#ifndef APP_H
#define APP_H

#include "Logic/Client.h"
#include "GUI/AuthFrame.h"
#include "GUI/MainWindow.h"
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
    // Deleted class members.
    App(const App&) = delete;
    App& operator=(const App&) = delete;
public:
    explicit App(QObject *parent = nullptr);

public slots:
    /** Reactions.
     * Each reaction has a prefix 'react'.
     */
    void reactAuthPassed();
    void reactDisruption();
};

#endif // APP_H
