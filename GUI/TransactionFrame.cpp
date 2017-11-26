#include "TransactionFrame.h"
#include "ui_TransactionFrame.h"

TransactionFrame::TransactionFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TransactionFrame)
{
    ui->setupUi(this);
    ui->cardChooser->addItem("");
}

TransactionFrame::~TransactionFrame()
{
    delete ui;
}

void TransactionFrame::reactForClose()
{
    this->close();
}
