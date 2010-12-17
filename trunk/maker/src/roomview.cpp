#include "roomview.h"
#include "arearect.h"

RoomView::RoomView(QWidget *parent) :
    QGraphicsView(parent)
{
    active_room = 0;

    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint &)));
}

void RoomView::addArea()
{
    updateRoomView();
    world->rooms()->addRoomArea(world->rooms()->at(active_room),
                                QRect(QPoint(20, 20), QSize(64, 64)));
    AreaRect *area_rect = new AreaRect(world->rooms()->at(active_room)->areas().last());
    scenes[world->rooms()->at(active_room)]->addItem(area_rect);
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

    bg = bg.scaled(world->getSize());

    world->rooms()->setRoomBackground(world->rooms()->at(active_room), bg);
    scenes[world->rooms()->at(active_room)]->addPixmap(world->rooms()->at(active_room)->background());
}

void RoomView::updateRoomView()
{
    if (!scenes.contains(world->rooms()->at(active_room)))
        scenes.insert(world->rooms()->at(active_room), new QGraphicsScene);

    setScene(scenes[world->rooms()->at(active_room)]);
}

void RoomView::setWorld(World *world)
{
    this->world = world;
}

void RoomView::changeActiveRoom(QModelIndex index)
{
    active_room = index.row();
    updateRoomView();
}
