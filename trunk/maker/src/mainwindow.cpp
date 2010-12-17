#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->rooms_list, SIGNAL(clicked(QModelIndex)),
            ui->room_view, SLOT(changeActiveRoom(QModelIndex)));

    wizard = new Wizard(this);
    wizard->show();
    connect(wizard, SIGNAL(accepted()), this, SLOT(resizeRoomView()));

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

void MainWindow::resizeRoomView()
{
    ui->room_view->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->room_view->setFixedSize(wizard->getSize());
    adjustSize();
}
