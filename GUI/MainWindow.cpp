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

void MainWindow::reactGotAccCards(unsigned cardsAmount)
{
    // TODO: Show all cards info.
    QMessageBox::information(this, "Information",
                             QString::number(cardsAmount));
}

void MainWindow::reactError(QString info)
{
    QMessageBox::information(this, "Error", info);
    freezeMode(false);
}
