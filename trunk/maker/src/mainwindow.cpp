#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    wizard(new Wizard(this)),
    world(NULL)
{
    ui->setupUi(this);

    rooms_list = new RoomsList;
    room_view = new RoomView;
    settings = new SettingsWidget;

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

    ui->centralWidget->setDisabled(true);

    connect(room_view, SIGNAL(roomChanged(Room*)), room_view, SIGNAL(selected(Room*)));
    connect(room_view, SIGNAL(selected(Room*)), settings, SLOT(updateRoomSettings(Room*)));
    connect(room_view, SIGNAL(selected(Area*)), settings, SLOT(updateAreaSettings(Area*)));
    connect(ui->action_Save, SIGNAL(triggered()), this, SLOT(saveProject()));
    connect(ui->action_Open, SIGNAL(triggered()), this, SLOT(openProject()));
    connect(ui->action_New, SIGNAL(triggered()), wizard, SLOT(show()));
    connect(ui->action_Quit, SIGNAL(triggered()), this, SLOT(close()));

    connect(rooms_list, SIGNAL(selected(QModelIndex)),
            room_view, SLOT(changeActiveRoom(QModelIndex)));

    connect(wizard, SIGNAL(accepted()), this, SLOT(newProject()));

    adjustSize();
}

MainWindow::~MainWindow()
{
    delete widget;
    delete rooms_list;
    delete settings;
    delete ui;
    delete wizard;
    delete world;
}

void MainWindow::saveProject()
{
    QString project_filename = QFileDialog::getSaveFileName(this, "Save project", QDir::homePath());
    QDir::setCurrent(project_filename.section("/", 0, -2));
    QFile file(project_filename);
    if (!file.open(QIODevice::WriteOnly))
        return;

    file.write(createXml().toAscii());
    file.close();

    QDir data_dir(QDir::currentPath() + "/" + world->name() + "_data");
    data_dir.mkpath(data_dir.absolutePath());

    QPixmap void_bg(world->size());
    void_bg.fill();

    for (int i = 0; i < world->rooms()->count(); i++)
    {
        QString bg_filename(data_dir.absolutePath() + "/" +
                            world->rooms()->at(i)->name() + "_bg.png");
        if (world->rooms()->at(i)->background().isNull())
            void_bg.save(bg_filename);
        else
            world->rooms()->at(i)->background().save(bg_filename);
    }
}

void MainWindow::openProject()
{
    QDomDocument doc("RoomsProjectFile");
    QString project_filename = QFileDialog::getOpenFileName(this, "Open project",
                                                            QDir::homePath(),
                                                            "Rooms project (*.rooms);;All files (*)");
    QDir::setCurrent(project_filename.section("/", 0, -2));
    QFile file(project_filename);
    if (!file.open(QIODevice::ReadOnly))
        return;
    if (!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    if (world != NULL)
        delete world;
    world = createWorld(doc);
    rooms_list->setWorld(world);
    room_view->setWorld(world);
    settings->setWorld(world);
    adjustSize();
    ui->centralWidget->setEnabled(true);
}

void MainWindow::newProject()
{
    if (world != NULL)
        delete world;
    world = new World(wizard->worldName(), wizard->worldSize());
    rooms_list->setWorld(world);
    room_view->setWorld(world);
    settings->setWorld(world);
    adjustSize();
    ui->centralWidget->setEnabled(true);
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
    //this block is useless for now because <img> contains only the filepath, which is
    //already included as "bg" attribute of <room>
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
        xroom.setAttribute("bg", "./" + world->name() + "_data/" +
                           world->rooms()->at(i)->name() + "_bg.png");
        QDomElement xareas = doc.createElement("areas");
        for (int j = 0; j < world->rooms()->at(i)->areas().count(); j++)
        {
            QDomElement xarea = doc.createElement("area");
            xarea.setAttribute("id", world->rooms()->at(i)->areas().at(j)->name());
            xarea.setAttribute("x", world->rooms()->at(i)->areas().at(j)->pos().x());
            xarea.setAttribute("y", world->rooms()->at(i)->areas().at(j)->pos().y());
            xarea.setAttribute("width", world->rooms()->at(i)->areas().at(j)->rect().width());
            xarea.setAttribute("height", world->rooms()->at(i)->areas().at(j)->rect().height());
            QDomElement xdo_event = doc.createElement("do_event");
            xdo_event.setAttribute("value", world->rooms()->at(i)->name() +
                                         world->rooms()->at(i)->areas().at(j)->name() +
                                         "_event");
            xarea.appendChild(xdo_event);
            xareas.appendChild(xarea);
        }
        xroom.appendChild(xareas);
        xrooms.appendChild(xroom);
    }
    xworld.appendChild(xrooms);
    //</rooms>

    //<events>
    QDomElement xevents = doc.createElement("events");
    for (int i = 0; i < world->rooms()->count(); i++)
    {
        for (int j = 0; j < world->rooms()->at(i)->areas().count(); j++)
        {
            QDomElement xevent = doc.createElement("event");
            xevent.setAttribute("id", world->rooms()->at(i)->name() +
                                      world->rooms()->at(i)->areas().at(j)->name() +
                                      "_event");
            QDomElement xrequirements = doc.createElement("requirements");
            xevent.appendChild(xrequirements);
            QDomElement xactions_if = doc.createElement("actions_if");
            for (int k = 0; k < world->rooms()->at(i)->areas().at(j)->actions().count(); k++)
            {
                QDomElement xaction = doc.createElement("action");
                xaction.setAttribute("id", world->rooms()->at(i)->areas().at(j)->actions().at(k)->typeToString());
                QDomElement xparam = doc.createElement("param");
                xparam.setAttribute("value", world->rooms()->at(i)->areas().at(j)->actions().at(k)->room());
                xaction.appendChild(xparam);
                xactions_if.appendChild(xaction);
            }
            xevent.appendChild(xactions_if);
            xevents.appendChild(xevent);
        }
    }
    xworld.appendChild(xevents);
    //</events>

    xml = doc.toString();
    return xml;
}

World *MainWindow::createWorld(const QDomDocument &doc)
{
    QDomElement xworld = doc.elementsByTagName("world").at(0).toElement();
    World *world = new World(xworld.attribute("name"), QSize(xworld.attribute("width").toInt(),
                                                             xworld.attribute("height").toInt()));

    //<images>
    //this block is useless for now because <img> contains only the filepath, which is
    //already included as "bg" attribute of <room>
    RoomsModel *rooms = world->rooms();
    QDomNode ximages = xworld.elementsByTagName("images").at(0);
    QDomElement ximg = ximages.firstChildElement();
    while (!ximg.isNull())
    {
        ximg = ximg.nextSiblingElement();
    }
    //</images>

    //<events>
    QHash<QString, QList<Action*> > events;
    QDomNode xevents = xworld.elementsByTagName("events").at(0);
    QDomElement xevent = xevents.firstChildElement();
    while (!xevent.isNull())
    {
        QList<Action*> actions_if;
        QDomNode xactions_if = xevent.elementsByTagName("actions_if").at(0);
        QDomElement xaction = xactions_if.firstChildElement();
        while (!xaction.isNull())
        {
            Action *action = new Action();
            action->setType(xaction.attribute("id"));
            QDomElement xparam = xaction.firstChildElement();
            action->setRoom(xparam.attribute("value"));
            actions_if.append(action);
            xaction = xaction.nextSiblingElement();
        }
        events.insert(xevent.attribute("id"), actions_if);
        xevent = xevent.nextSiblingElement();
    }
    //</events>

    //<rooms>
    QDomNode xrooms = xworld.elementsByTagName("rooms").at(0);
    QDomElement xroom = xrooms.firstChildElement();
    while (!xroom.isNull())
    {
        rooms->appendRoom();
        Room *room = rooms->at(rooms->count()-1);
        QString id(xroom.attribute("id"));
        QPixmap bg(xroom.attribute("bg"));
        bg = bg.scaled(world->size());
        room->setName(id);
        room->setBackground(bg);
        //<areas>
        QDomNode xareas = xroom.firstChild();
        QDomElement xarea = xareas.firstChildElement();
        while (!xarea.isNull())
        {
            QString id(xarea.attribute("id"));
            QPoint pos(xarea.attribute("x").toInt(),
                       xarea.attribute("y").toInt());
            QSize size(xarea.attribute("width").toInt(),
                       xarea.attribute("height").toInt());
            Area *area = room->addArea(pos, size);
            area->setName(id);
            QDomElement xdo_event = xarea.firstChildElement();
            area->setActions(events[xdo_event.attribute("value")]);
            xarea = xarea.nextSiblingElement();
        }
        //</areas>
        xroom = xroom.nextSiblingElement();
    }
    //</rooms>

    return world;
}
