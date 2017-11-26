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
    ui->refreshButton->setDisabled(mode);
    ui->settingsButton->setDisabled(mode);
}

void MainWindow::requestForAccMoney()
{
    setWaitingMode(true);
    emit callForAccMoney();
}

void MainWindow::requestForCards()
{
    setWaitingMode(true);
    emit callForAccCards();
}

void MainWindow::requestForPayments()
{
    setWaitingMode(true);
    emit callForPaymentsAmount();
}

void MainWindow::requestForTransaction()
{
    setWaitingMode(true);
    emit callForTransaction();
}

void MainWindow::reactGotAccMoney(quint64 money)
{
    ui->accMoneyValueLabel->setText(QString::number(money));
    setWaitingMode(false);
}

void MainWindow::reactGotAccCards(QMap<quint64, quint8>& cards)
{
    QMapIterator<quint64, quint8> iter(cards);
    qDebug("cards displaying started.");
    while (iter.hasNext())
    {
        iter.next();
        QString str = QString::number(iter.key());
        ui->cardsView->addItem(str.append(": ").
            append(QString::number(iter.value())));
    }
    qDebug("cards displaying finished.");

    setWaitingMode(false);
}

void MainWindow::reactGotPaymentsAmount(unsigned amount)
{
    // TODO: Show all payments info.
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
