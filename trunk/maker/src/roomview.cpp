#include "roomview.h"
#include "arearect.h"
#include <QMouseEvent>

RoomView::RoomView()
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setRenderHint(QPainter::Antialiasing);

    setFixedSize(600, 500);

    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint &)));
}

void RoomView::setWorld(World *world)
{
    setDisabled(true);
    _world = world;
    rooms = _world->rooms();
    connect(rooms, SIGNAL(activeRoomChanged(Room*)), this, SLOT(updateRoomView(Room*)));
    setFixedSize(_world->size());
}

void RoomView::addArea()
{
    updateRoomView(activeRoom());
    Area *area = activeRoom()->addArea(QPoint(0, 0), QSize(64, 64));
    AreaRect *area_rect = new AreaRect(area);
    scenes[activeRoom()]->addItem(area_rect);
}

void RoomView::showContextMenu(const QPoint &point)
{
    QMenu *menu = new QMenu;
    menu->addAction(tr("Set background"), this, SLOT(setBackground()));
    menu->addSeparator();
    menu->addAction(tr("Add an area"), this, SLOT(addArea()));
    menu->exec(mapToGlobal(point));
    delete menu;
}

void RoomView::setBackground()
{
    updateRoomView(activeRoom());
    QString bgFile = QFileDialog::getOpenFileName(this,"Select the background file",
                                                  QDir::currentPath(),
                                                  "Images (*.png *.xpm *.jpg *.gif)");
    QPixmap bg(bgFile);
    if (bg.isNull())
        return;

    bg = bg.scaled(_world->size());

    activeRoom()->setBackground(bg);
    scenes[activeRoom()]->addPixmap(bg);
}

void RoomView::updateRoomView(Room *room)
{
    if (room == 0)
    {
        setScene(NULL);
        setDisabled(true);
        return;
    }

    setEnabled(true);
    if (!scenes.contains(room))
    {
        scenes.insert(room, new QGraphicsScene(QRectF(QPoint(0, 0), _world->size())));
        scenes[room]->addPixmap(room->background());
        for (int i = 0; i < activeRoom()->areas().count(); i++)
        {
            AreaRect *area_rect = new AreaRect(room->areas().at(i));
            scenes[room]->addItem(area_rect);
        }
    }

    setScene(scenes[room]);
    emit selected(room);
}

Room *RoomView::activeRoom() const
{
    return rooms->activeRoom();
}

void RoomView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    QGraphicsItem *item = itemAt(event->pos());
    if (item == 0 || item->zValue() == 0)
        emit selected(activeRoom());
    else
    {
        Area *area = ((AreaRect *)item)->area();
        activeRoom()->setActiveArea(area);
        emit selected(area);
    }
}
