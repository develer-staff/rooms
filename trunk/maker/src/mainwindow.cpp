#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    wizard = new Wizard(this);
    wizard->exec();

    ui->room_view->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->room_view->setFixedSize(wizard->getSize());
    this->adjustSize();

    world = new World(wizard->getName(), wizard->getSize());
    world->rooms()->appendRoom("Room 0");

    ui->room_view->setWorld(world);
    ui->rooms_list->setWorld(world);
    ui->rooms_list->setModel(world->roomsModel());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete wizard;
}
