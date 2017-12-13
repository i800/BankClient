#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    inline const QList<QString>& cardsList()
    {
        return _cardsList;
    }

public slots:
    /**
     * Requests to the client.
     * Each request to the client
     * has a prefix 'request'.
     */
    void requestForAccInfo();
    void requestForPeriodicalPaymentsIds();
    void requestForCards();
    void requestForTransaction();
    void requestForPCancelling();
    void requestForTransactionDone(quint64, quint64, quint64, QString&);
    void requestForCancellingDone(quint64);
    void requestForQuit();

    /**
      * Reactions.
      * Each reaction has a prefix 'react'.
      */
    void reactGotAccMoney(quint64);
    void reactGotAccCards(QMap<quint64, quint8>&);
    void reactGotPayments(QMap<quint64, QPair<quint64, quint64>>&);
    void reactError(QString);

    void setWaitingMode(const bool);
    void setLoggedInCard(const quint64);
private:
    Ui::MainWindow *ui;
    QList<QString> _cardsList;

signals:
    void callForAccMoney(quint64);
    void callForPayments(quint64);
    void callForPeriodicalPaymentsIds(quint64);
    void callForAccCards();
    void callForTransaction();
    void callForPCancelling();
    void callForTransactionDone(quint64, quint64, quint64, quint64, QString&);
    void callForCancellingDone(quint64);
    void callForQuit();
};

#endif // MAINWINDOW_H
