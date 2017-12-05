#include "TransactionFrame.h"
#include "ui_TransactionFrame.h"
#include <QMessageBox>

TransactionFrame::TransactionFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TransactionFrame),
    _firstInit(true)
{
    ui->setupUi(this);
    ui->cardChooser->addItem("");
}

TransactionFrame::~TransactionFrame()
{
    delete ui;
}

void TransactionFrame::setCards(const QList<QString>& cardsList)
{
    QListIterator<QString> iter(cardsList);
    while (iter.hasNext())
    {
        ui->cardChooser->addItem(iter.next());
    }

    _firstInit = false;
}

void TransactionFrame::requestForTransaction()
{
    bool cardOk(false);
    quint64 cardNumber = ui->cardChooser->currentText().toULongLong(&cardOk);
    bool amountOk(false);
    quint64 amount = ui->amountLine->toPlainText().toULongLong(&amountOk);
    if (cardOk && amountOk)
    {
       QString comment(ui->commentArea->toPlainText());
       emit callForTransaction(cardNumber, amount, comment);
    }
    else
    {
        QMessageBox::information(0, "Error", "Check all the fields.");
    }

    emit callForClose();
}

void TransactionFrame::reactForClose()
{
    ui->commentArea->clear();
    this->close();
}

void TransactionFrame::closeEvent(QCloseEvent*)
{
    emit callForClose();
}
