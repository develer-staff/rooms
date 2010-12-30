#include "roomslist.h"
#include <QMenu>

RoomsList::RoomsList()
{
    setFixedWidth(200);
    setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint &)));
}

void RoomsList::setWorld(World *world)
{
    _world = world;
    rooms = _world->rooms();
    setModel(rooms);
}

void RoomsList::showContextMenu(const QPoint &point)
{
    QMenu *menu = new QMenu;
    menu->addAction(tr("Add a room"), this, SLOT(addRoom()));
    menu->exec(mapToGlobal(point));
    delete menu;
}

void RoomsList::addRoom()
{
    rooms->appendRoom();
    const QModelIndex index = model()->index(rooms->count()-1, 0);
    setCurrentIndex(index);
}

void RoomsList::selectionChanged(const QItemSelection &new_selected, const QItemSelection &old_selected)
{
    Q_UNUSED(old_selected);
    emit selected(new_selected.indexes().first());
    Room *selected_room = rooms->at(new_selected.indexes().first().row());
    rooms->setActiveRoom(selected_room);
}
