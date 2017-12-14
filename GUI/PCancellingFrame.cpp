#include "PCancellingFrame.h"
#include "ui_PCancellingFrame.h"
#include <QMessageBox>

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
    ui->idChooser->clear();
    while(iter.hasNext())
    {
        iter.next();
        const QPair<quint64, quint64>& val = iter.value();
        ui->idChooser->addItem(QString("%1 CUU to %2").arg(QString::number(val.first),QString::number(val.first)), iter.key());
        //ui->idChooser->addItem(QString::number(iter.key()));
    }
}

void PCancellingFrame::requestForPCancelling()
{
    bool idOk(false);
    quint64 id = ui->idChooser->currentData().toULongLong(&idOk);
    if (idOk)
    {
        emit callForPCancelling(id);
    }
    else
    {
        QMessageBox::information(0, "Error", "Check the input.");
    }

    requestForClose();
}

void PCancellingFrame::requestForClose()
{
    emit callForClose();
    reactForClose();
}

void PCancellingFrame::reactForClose()
{
    this->close();
}

void PCancellingFrame::closeEvent(QCloseEvent*)
{
    emit callForClose();
    reactForClose();
}
