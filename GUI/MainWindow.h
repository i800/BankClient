#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    /**
     * Requests to the client.
     * Each request to the client
     * has a prefix 'request'.
     */
    void requestForAccMoney();
    void requestForCards();
    void requestForTransaction();
    void requestForQuit();
    /**
      * Reactions.
      * Each reaction has a prefix 'react'.
      */
    void reactGotAccMoney(quint64);
    void reactGotAccCards(QMap<quint64, quint8>&);
    void reactGotPaymentsAmount(uint);
    void reactError(QString);

    void setWaitingMode(const bool);
    void setLoggedInCard(const quint64);
private:
    Ui::MainWindow *ui;

signals:
    void callForAccInfo();
    void callForAccCards();
    void callForTransaction();
};

#endif // MAINWINDOW_H
