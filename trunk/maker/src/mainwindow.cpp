#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    wizard = new Wizard(this);
    wizard->exec();

    ui->roomView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->roomView->setFixedSize(wizard->getSize());
    this->adjustSize();

    world = new World(wizard->getName(), wizard->getSize());
    world->addRoom("Example Room");

    ui->roomView->setWorld(world);
    ui->roomsList->setModel(world->roomsModel());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete wizard;
}
