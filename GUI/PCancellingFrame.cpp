#include "PCancellingFrame.h"
#include "ui_PCancellingFrame.h"

PCancellingFrame::PCancellingFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::PCancellingFrame)
{
    ui->setupUi(this);
}

PCancellingFrame::~PCancellingFrame()
{
    delete ui;
}

void PCancellingFrame::setIds()
{

}

void PCancellingFrame::requestForPCancelling()
{

}

void PCancellingFrame::reactForClose()
{
    ui->idChooser->clear();
    this->close();
}

void PCancellingFrame::closeEvent(QCloseEvent*)
{
    emit callForClose();
}
