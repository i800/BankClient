#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnBottomHint
                       | Qt::MSWindowsFixedSizeDialogHint);
    this->setMinimumSize(size());
    this->setMaximumSize(size());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setWaitingMode(const bool mode)
{
    ui->makeTransactionButton->setDisabled(mode);
}

void MainWindow::requestForAccMoney()
{
    setWaitingMode(true);
    emit callForAccMoney();
}

void MainWindow::requestForCards()
{
    setWaitingMode(true);
    emit callForAccCardsAmount();
}

void MainWindow::requestForPayments()
{
    setWaitingMode(true);
    emit callForPaymentsAmount();
}

void MainWindow::reactGotAccMoney(quint64 money)
{
    QString str("Your money: ");
    QMessageBox::information(this, "Information",
                   str.append(QString::number(money)));
    setWaitingMode(false);
}

void MainWindow::reactGotAccCardsAmount(unsigned cardsAmount)
{
    // TODO: Show all cards info.
    QString str("Your number of cards: ");
    QMessageBox::information(this, "Information",
                             str.append(QString::number(cardsAmount)));
    setWaitingMode(false);
}

void MainWindow::reactGotPaymentsAmount(unsigned amount)
{
    // TODO: Show all cards info.
        QString str("Your number of payments: ");
    QMessageBox::information(this, "Information",
                             str.append(QString::number(amount)));
    setWaitingMode(false);
}

void MainWindow::reactError(QString info)
{
    QMessageBox::information(this, "Error", info);
    setWaitingMode(false);
}
