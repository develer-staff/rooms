#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDomDocument>
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
    connect(ui->action_Save, SIGNAL(triggered()), this, SLOT(saveProject()));

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

void MainWindow::saveProject()
{
    QString project_filename = QFileDialog::getSaveFileName(this, "Save project", QDir::currentPath());
    QFile file(project_filename);
    if (!file.open(QIODevice::WriteOnly))
        return;

    file.write(createXml().toAscii());

    file.close();
}

QString MainWindow::createXml() const
{
    QString xml;
    QDomDocument doc("RoomsProjectFile");

    QDomElement xworld = doc.createElement("world");
    xworld.setAttribute("version", "ROOMS_VANILLA");
    xworld.setAttribute("name", world->name());
    xworld.setAttribute("width", world->size().width());
    xworld.setAttribute("height", world->size().height());
    xworld.setAttribute("start", 0);
    doc.appendChild(xworld);

    //<images>
    QDomElement ximages = doc.createElement("images");
    for (int i = 0; i < world->rooms()->count(); i++)
    {
        QDomElement ximg = doc.createElement("img");
        ximg.setAttribute("file", world->rooms()->at(i)->name());
        ximages.appendChild(ximg);
    }
    xworld.appendChild(ximages);
    //</images>

    //<rooms>
    QDomElement xrooms = doc.createElement("rooms");
    for (int i = 0; i < world->rooms()->count(); i++)
    {
        QDomElement xroom = doc.createElement("room");
        xroom.setAttribute("id", world->rooms()->at(i)->name());
        xroom.setAttribute("bg", world->rooms()->at(i)->name());
        QDomElement xareas = doc.createElement("areas");
        for (int j = 0; j < world->rooms()->at(i)->areas().count(); j++)
        {
            QDomElement xarea = doc.createElement("area");
            xarea.setAttribute("id", world->rooms()->at(i)->areas().at(j)->name());
            xarea.setAttribute("x", world->rooms()->at(i)->areas().at(j)->rect().x());
            xarea.setAttribute("y", world->rooms()->at(i)->areas().at(j)->rect().y());
            xarea.setAttribute("width", world->rooms()->at(i)->areas().at(j)->rect().width());
            xarea.setAttribute("height", world->rooms()->at(i)->areas().at(j)->rect().height());
            xareas.appendChild(xarea);
        }
        xroom.appendChild(xareas);
        xrooms.appendChild(xroom);
    }
    xworld.appendChild(xrooms);
    //</rooms>

    xml = doc.toString();
    return xml;
}
