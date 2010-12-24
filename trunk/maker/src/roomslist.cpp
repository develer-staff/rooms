#include "roomslist.h"
#include <QMenu>

RoomsList::RoomsList(World *world, QWidget *parent) :
    QListView(parent)
{
    setWorld(world);

    setFixedWidth(200);
    setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint &)));
}

void RoomsList::setWorld(World *world)
{
    _world = world;
    setModel(_world->rooms());
}

void RoomsList::showContextMenu(const QPoint &point)
{
    QMenu *menu = new QMenu;
    menu->addAction(tr("Add a room"), this, SLOT(addRoom()));
    menu->exec(mapToGlobal(point));
}

void RoomsList::addRoom()
{
    _world->rooms()->appendRoom();

    const QModelIndex index = model()->index(_world->rooms()->count()-1, 0);
    setCurrentIndex(index);
}

void RoomsList::selectionChanged(const QItemSelection &new_selected, const QItemSelection &old_selected)
{
    emit selected(new_selected.indexes().first());
}
