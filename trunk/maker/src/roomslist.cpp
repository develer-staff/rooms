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
    if (indexAt(point).isValid())
    {
        menu->addAction(tr("Remove %1").arg(rooms->activeRoom()->name()),
                        this, SLOT(removeRoom()));
    }
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

void RoomsList::removeRoom()
{
    int room_index = rooms->removeRoom();
    if (room_index >= rooms->count())
        room_index--;

    if (room_index == -1)
    {
        Room *room = 0;
        rooms->setActiveRoom(room);
    }
    else
    {
        rooms->setActiveRoom(rooms->at(room_index));
        setCurrentIndex(rooms->index(room_index));
    }
}

void RoomsList::selectionChanged(const QItemSelection &new_selected, const QItemSelection &old_selected)
{
    Q_UNUSED(old_selected);
    Room *selected_room = rooms->at(new_selected.indexes().first().row());
    emit selected(selected_room);
    rooms->setActiveRoom(selected_room);
}
