#include "roomslist.h"
#include <QMenu>

RoomsList::RoomsList(QWidget *parent) :
    QListView(parent)
{
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint &)));
}

void RoomsList::setWorld(World *world)
{
    this->world = world;
}

void RoomsList::showContextMenu(const QPoint &point)
{
    QMenu *menu = new QMenu;
    menu->addAction(tr("Add a room"), this, SLOT(addRoom()));
    menu->exec(mapToGlobal(point));
}

void RoomsList::addRoom()
{
    world->rooms()->appendRoom();

    const QModelIndex index = model()->index(world->rooms()->count()-1, 0);
    setCurrentIndex(index);
    emit clicked(index);

}
