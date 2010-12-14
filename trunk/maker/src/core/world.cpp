#include "world.h"
#include "roomsmodel.h"

World::World(const QString &name, const QSize &size, QObject *parent) :
    QObject(parent)
{
    this->name = name;
    this->size = size;
    _rooms = new RoomsModel(this);
}

void World::addRoom(QString const& name)
{
    Room *room = new Room(name);
    _rooms->appendRoom(room);
}

int World::countRooms() const
{
    return _rooms->rowCount(QModelIndex());
}

Room *World::getRoom(int index) const
{
    return _rooms->at(index);
}

QSize World::getSize() const
{
    return size;
}

QAbstractItemModel *World::rooms() const
{
    return _rooms;
}
