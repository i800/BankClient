#include "TransactionFrame.h"
#include "ui_TransactionFrame.h"

TransactionFrame::TransactionFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TransactionFrame)
{
    ui->setupUi(this);
}

TransactionFrame::~TransactionFrame()
{
    delete ui;
}
