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
