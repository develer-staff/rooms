#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    wizard(new Wizard(this)),
    world(new World(wizard->worldName(), wizard->worldSize()))
{
    ui->setupUi(this);

    rooms_list = new RoomsList(world);
    room_view = new RoomView(world);
    settings = new SettingsWidget(world);

    ui->splitter->addWidget(rooms_list);
    widget = new QWidget;
    layout = new QGridLayout;
    vspacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    hspacer = new QSpacerItem(0, 0, QSizePolicy::Expanding);
    layout->addWidget(room_view, 0, 0);
    layout->addItem(hspacer, 0, 1);
    layout->addItem(vspacer, 1, 0, 1, 2);
    layout->setMargin(0);
    widget->setLayout(layout);
    ui->splitter->addWidget(widget);
    ui->splitter->addWidget(settings);

    connect(room_view, SIGNAL(roomChanged(Room*)), room_view, SIGNAL(selected(Room*)));
    connect(room_view, SIGNAL(selected(Room*)), settings, SLOT(updateRoomSettings(Room*)));
    connect(room_view, SIGNAL(selected(Area*)), settings, SLOT(updateAreaSettings(Area*)));

    connect(rooms_list, SIGNAL(clicked(QModelIndex)),
            room_view, SLOT(changeActiveRoom(QModelIndex)));

    connect(wizard, SIGNAL(accepted()), this, SLOT(resizeRoomView()));

    resizeRoomView();
    wizard->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete wizard;
}

void MainWindow::resizeRoomView()
{
    room_view->setFixedSize(wizard->worldSize());
    world->setSize(wizard->worldSize());
    adjustSize();
}
