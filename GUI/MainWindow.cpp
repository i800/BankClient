#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::freezeMode(const bool mode)
{
    // TODO: freeze mode.
}

void MainWindow::reactGotAccMoney(quint64 money)
{
    QString str("Your money: ");
    QMessageBox::information(this, "Information",
                   str.append(QString::number(money)));
}

void MainWindow::reactGotAccCardsAmount(unsigned cardsAmount)
{
    // TODO: Show all cards info.
    QString str("Your number of cards: ");
    QMessageBox::information(this, "Information",
                             str.append(QString::number(cardsAmount)));
}

void MainWindow::reactGotPaymentsAmount(unsigned amount)
{
    // TODO: Show all cards info.
        QString str("Your number of payments: ");
    QMessageBox::information(this, "Information",
                             str.append(QString::number(amount)));
}

void MainWindow::reactError(QString info)
{
    QMessageBox::information(this, "Error", info);
    freezeMode(false);
}
