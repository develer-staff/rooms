#include "roomslist.h"
#include <QMenu>

RoomsList::RoomsList(World *world, QWidget *parent) :
    QListView(parent)
{
    _world = world;
    setModel(_world->rooms());

    setFixedWidth(200);
    setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint &)));
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
    emit clicked(index);

}
