#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wizard = new Wizard(this);
    wizard->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete wizard;
}
