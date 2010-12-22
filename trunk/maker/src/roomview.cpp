#include "roomview.h"
#include "arearect.h"
#include <QMouseEvent>

RoomView::RoomView(World *world, QWidget *parent) :
    QGraphicsView(parent)
{
    _world = world;
    world->rooms()->appendRoom();
    active_room = world->rooms()->at(0);

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setRenderHint(QPainter::Antialiasing);

    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint &)));
}

void RoomView::addArea()
{
    updateRoomView();
    active_room->addArea(QRect(QPoint(20, 20), QSize(64, 64)));
    AreaRect *area_rect = new AreaRect(active_room->areas().last());
    scenes[active_room]->addItem(area_rect);
}

void RoomView::showContextMenu(const QPoint &point)
{
    QMenu *menu = new QMenu;
    menu->addAction(tr("Set background"), this, SLOT(setBackground()));
    menu->addSeparator();
    menu->addAction(tr("Add an area"), this, SLOT(addArea()));
    menu->exec(mapToGlobal(point));
}

void RoomView::setBackground()
{
    updateRoomView();
    QString bgFile = QFileDialog::getOpenFileName(this,"Select the background file",
                                                  QDir::currentPath(),
                                                  "Images (*.png *.xpm *.jpg *.gif)");
    QPixmap bg(bgFile);
    if (bg.isNull())
        return;

    bg = bg.scaled(_world->size());

    active_room->setBackground(bg);
    scenes[active_room]->addPixmap(bg);
}

void RoomView::updateRoomView()
{
    if (!scenes.contains(active_room))
        scenes.insert(active_room,
                      new QGraphicsScene(QRectF(QPoint(0, 0), _world->size())));

    setScene(scenes[active_room]);
}

void RoomView::changeActiveRoom(QModelIndex index)
{
    active_room = _world->rooms()->at(index.row());
    updateRoomView();
    emit roomChanged(active_room);
}

void RoomView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    QGraphicsItem *item = itemAt(event->pos());
    if (item == 0 || item->zValue() == 0)
        emit selected(active_room);
    else
        emit selected(((AreaRect *)item)->area());
}
