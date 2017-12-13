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
    emit callForIds();
}

void PCancellingFrame::setIds(QMap<quint64,QPair<quint64,quint64>>& payments)
{
    QMapIterator<quint64,QPair<quint64,quint64>> iter(payments);
    while (iter.hasNext())
    {
        iter.next();
        ui->idChooser->addItem(QString::number(iter.key()));
    }
}

void PCancellingFrame::requestForPCancelling()
{
    // TODO: Cancel a periodical transaction.
}

void PCancellingFrame::requestForClose()
{
    emit callForClose();
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
