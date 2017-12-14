#include "AuthFrame.h"
#include "ui_AuthFrame.h"
#include "QMessageBox"

AuthFrame::AuthFrame(QWidget *parent):
    QFrame(parent),
    ui(new Ui::AuthFrame)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint
                       | Qt::WindowStaysOnBottomHint);

#ifndef NDEBUG
    QMessageBox::information(0, "DEBUG MODE", "TO TEST THE PROGRAM\nUSE CARD 1 WITH PASSWORD PIN1.");
#endif
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
    ui->quitButton->setDisabled(value);
}

void AuthFrame::requestForAuth()
{
    QString cardnum = ui->in_cardNum->text();
    QString pass = ui->in_password->text();
//    qDebug("pass:");
//    qDebug(pass.toStdString().c_str());
    bool cardnumOk(false);
    quint64 cardnumConv = cardnum.toULongLong(&cardnumOk);
    if (cardnumOk && pass.length() == 4)
    {
        emit callForAuth(cardnumConv, pass);
        setWaitingMode(true);
    }
    else
    {
        QMessageBox::information(this, "Ooops..", "Invalid input. Please, check it.");
    }
}

void AuthFrame::requestForQuit()
{
    exit(0);
}

void AuthFrame::reactAuthFailed()
{
    QMessageBox::information(this, "Error", "Invalid card number or password.");
    setWaitingMode(false);
}
