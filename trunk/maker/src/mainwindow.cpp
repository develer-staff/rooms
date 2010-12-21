#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->room_view, SIGNAL(selected(Room*)), this, SLOT(updateRoomSettings(Room*)));
    connect(ui->room_view, SIGNAL(selected(Area*)), this, SLOT(updateAreaSettings(Area*)));

    connect(ui->rooms_list, SIGNAL(clicked(QModelIndex)),
            ui->room_view, SLOT(changeActiveRoom(QModelIndex)));

    wizard = new Wizard(this);
    wizard->show();
    connect(wizard, SIGNAL(accepted()), this, SLOT(resizeRoomView()));

    world = new World(wizard->worldName(), wizard->worldSize());

    ui->room_view->setWorld(world);
    ui->rooms_list->setWorld(world);
    ui->rooms_list->setModel(world->rooms());

    resizeRoomView();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete wizard;
}

void MainWindow::resizeRoomView()
{
    ui->room_view->setFixedSize(wizard->worldSize());
    world->setSize(wizard->worldSize());
    adjustSize();
}

void MainWindow::updateRoomSettings(Room *room)
{
    ui->room_name->setText(room->name());
}
