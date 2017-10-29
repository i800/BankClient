#include "AuthFrame.h"
#include "ui_AuthFrame.h"
#include "QMessageBox"

AuthFrame::AuthFrame(QWidget *parent):
    QFrame(parent),
    ui(new Ui::AuthFrame)
{
    ui->setupUi(this);
}

AuthFrame::~AuthFrame()
{
    delete ui;
}

void AuthFrame::setWaitingMode(const bool value)
{
    ui->in_cardNum->setDisabled(value);
    ui->in_password->setDisabled(value);
    ui->pushButton->setDisabled(value);
}

void AuthFrame::requestForAuth()
{
    QString cardnum = ui->in_cardNum->text();
    QString pass = ui->in_password->text();
    bool cardnumOk(false);
    bool passOk(false);
    long long cardnumConv = cardnum.toLongLong(&cardnumOk);
    short passConv = pass.toShort(&passOk);
    if (cardnumOk && cardnum.length() == 19 && passOk && pass.length() == 4)
    {
        emit callForAuth(cardnumConv, passConv);
        setWaitingMode(true);
    }
    else
    {
        QMessageBox::information(this, "Ooops..", "Invalid input. Please, check it.");
    }
}

void AuthFrame::reactAuthFailed()
{
    QMessageBox::information(this, "Error", "Invalid card number or password.");
    setWaitingMode(false);
}
