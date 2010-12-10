#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setDisabled(true);
    wizard = new Wizard(this);
    wizard->exec();
    this->setEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete wizard;
}
