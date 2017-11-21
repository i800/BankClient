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
    void setWaitingMode(const bool);
public slots:
    /**
     * Requests to the client.
     * Each request to the client
     * has a prefix 'request'.
     */
    void requestForAccMoney();
    void requestForCards();
    void requestForPayments();
    /**
      * Reactions.
      * Each reaction has a prefix 'react'.
      */
    void reactGotAccMoney(quint64);
    void reactGotAccCardsAmount(uint);
    void reactGotPaymentsAmount(uint);
    void reactError(QString);
private:
    Ui::MainWindow *ui;

signals:
    void callForAccMoney();
    void callForAccCardsAmount();
    void callForPaymentsAmount();
};

#endif // MAINWINDOW_H
