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

void RoomView::addArea(const QPoint &pos, const QSize &size)
{
    updateRoomView(activeRoom());
    Area *area = activeRoom()->addArea(pos, size);
    AreaRect *area_rect = new AreaRect(area);
    scenes[activeRoom()]->addItem(area_rect);
}

void RoomView::showContextMenu(const QPoint &point)
{
    QMenu *menu = new QMenu;
    menu->addAction(tr("Set background"), this, SLOT(setBackground()));
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
    {
        last_pos = event->pos();
        emit selected(activeRoom());
    }
    else
    {
        last_pos = QPoint();
        Area *area = ((AreaRect *)item)->area();
        activeRoom()->setActiveArea(area);
        emit selected(area);
    }
}

void RoomView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
    //TODO: drawing temp rectangle
}

void RoomView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
    if (!last_pos.isNull() && last_pos != event->pos())
    {
        QPoint top_left;
        top_left.setX((last_pos.x() < event->pos().x()) ? last_pos.x() : event->pos().x());
        top_left.setY((last_pos.y() < event->pos().y()) ? last_pos.y() : event->pos().y());
        QPoint bottom_right;
        bottom_right.setX((last_pos.x() > event->pos().x()) ? last_pos.x() : event->pos().x());
        bottom_right.setY((last_pos.y() > event->pos().y()) ? last_pos.y() : event->pos().y());
        addArea(top_left, QSize(bottom_right.x() - top_left.x(),
                                bottom_right.y() - top_left.y()));
    }
    last_pos = QPoint();
}
