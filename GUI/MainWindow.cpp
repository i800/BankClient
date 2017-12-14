#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent):
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

quint64 MainWindow::currentCard() const
{
    QList<QListWidgetItem*> cards = ui->cardsView->selectedItems();
    if (cards.empty())
    {
        return ui->loggedInCardValueLabel->text().toULongLong();
    }
    else
    {
        return cards.first()->text().toULongLong();
    }
}

void MainWindow::setWaitingMode(const bool mode)
{
    ui->makeTransactionButton->setDisabled(mode);
    ui->cpButton->setDisabled(mode);
    ui->refreshButton->setDisabled(mode);
    ui->settingsButton->setDisabled(mode);
    ui->cardsView->setDisabled(mode);
    ui->quitButton->setDisabled(mode);
}

void MainWindow::setLoggedInCard(const quint64 cardNumber)
{
    ui->loggedInCardValueLabel->setText(QString::number(cardNumber));
}

void MainWindow::requestForAccInfo()
{
    setWaitingMode(true);

    QList<QListWidgetItem*> cards = ui->cardsView->selectedItems();
    if (cards.empty())
    {
        emit callForAccMoney(ui->loggedInCardValueLabel->text().toULongLong());
    }
    else
    {
        emit callForAccMoney(cards.first()->text().toULongLong());
    }
}

void MainWindow::requestForAuthors()
{
    QMessageBox::information(this, "Authors", "ANDREW GOMENYUK\nDMYTRO DEHTYARENKO\nUSATSCHOFF CYRIL\nKHODIENKO DANIEL");
}

void MainWindow::requestForPeriodicalPaymentsIds()
{
    QList<QListWidgetItem*> cards = ui->cardsView->selectedItems();
    if (cards.empty())
    {
        emit callForPeriodicalPaymentsIds(ui->loggedInCardValueLabel->text().toULongLong());
    }
    else
    {
        emit callForPeriodicalPaymentsIds(cards.first()->text().toULongLong());
    }
}

void MainWindow::requestForCards()
{
    setWaitingMode(true);
    emit callForAccCards();
}

void MainWindow::requestForTransaction()
{
    setWaitingMode(true);
    emit callForTransaction();
}

void MainWindow::requestForPCancelling()
{
    setWaitingMode(true);
    emit callForPCancelling();
}

void MainWindow::requestForTransactionDone(quint64 to, quint64 amount, quint64 time, QString& comment)
{
    setWaitingMode(true);
    QList<QListWidgetItem*> cards = ui->cardsView->selectedItems();
    quint64 from(0);
    if (cards.empty())
    {
        from = ui->loggedInCardValueLabel->text().toULongLong();
    }
    else
    {
        from = cards.first()->text().toULongLong();
    }

    emit callForTransactionDone(from, to, amount, time, comment);
}

void MainWindow::requestForQuit()
{
    callForQuit();
}

void MainWindow::reactGotAccMoney(quint64 money)
{
    ui->accMoneyValueLabel->setText(QString::number(money));

    QList<QListWidgetItem*> cards = ui->cardsView->selectedItems();
    if (cards.empty())
    {
        emit callForPayments(ui->loggedInCardValueLabel->text().toULongLong());
    }
    else
    {
        emit callForPayments(cards.first()->text().toULongLong());
    }

    setWaitingMode(false);
}

void MainWindow::reactGotAccCards(QMap<quint64, quint8>& cards)
{
    QMapIterator<quint64, quint8> iter(cards);
    while (iter.hasNext())
    {
        iter.next();
        QString str = QString::number(iter.key());
        ui->cardsView->addItem(str);
        _cardsList.append(str);
    }

    setWaitingMode(false);
    requestForAccInfo();
}

void MainWindow::reactGotPayments(QMap<quint64, QPair<quint64, quint64>>& payments)
{
    ui->paymentsView->clear();

    QMapIterator<quint64, QPair<quint64, quint64>> iter(payments);
    while (iter.hasNext())
    {
        iter.next();
        QString pId = QString::number(iter.key());
        QString pTo = QString::number(iter.value().first);
        QString pAm = QString::number(iter.value().second);
        ui->paymentsView->addItem(QString("ID(").append(pId).append(") to card: ")
                            .append(pTo).append(" amount (c. u.): ").append(pAm));
    }
    setWaitingMode(false);
}

void MainWindow::reactError(QString info)
{
    QMessageBox::information(this, "Error", info);
    setWaitingMode(false);
}
