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
    void freezeMode(const bool);
public slots:
    /**
      * Reactions.
      * Each reaction has a prefix 'react'.
      */
    void reactGotAccMoney(quint64);
    void reactGotAccCards(unsigned);
    // void reactGotPayments()
    void reactError(QString);
private:
    Ui::MainWindow *ui;

signals:
};

#endif // MAINWINDOW_H
