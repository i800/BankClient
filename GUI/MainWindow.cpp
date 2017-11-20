#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::freezeMode(const bool mode)
{
    // FREEZE IT, DANICH!!!
}

void MainWindow::reactError(QString info)
{
    QMessageBox::information(this, "Error", info);
    freezeMode(false);
}
