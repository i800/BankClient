#include "TransactionFrame.h"
#include "ui_TransactionFrame.h"

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

void TransactionFrame::reactForClose()
{
    ui->textEdit->clear();
    this->close();
}

void TransactionFrame::closeEvent(QCloseEvent*)
{
    emit callForClose();
}
