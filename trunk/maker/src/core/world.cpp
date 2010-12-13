#include "world.h"
#include "roomsmodel.h"

World::World(const QString &name, const QSize &size, QObject *parent) :
    QObject(parent)
{
    this->name = name;
    this->size = size;
    rooms = new RoomsModel(this);
}

void World::addRoom(QString const& name)
{
    Room *room = new Room(name);
    rooms->appendRoom(room);
}

int World::countRooms() const
{
    return rooms->rowCount(QModelIndex());
}

Room *World::getRoom(int index) const
{
    return rooms->at(index);
}

QSize World::getSize() const
{
    return size;
}

QAbstractItemModel *World::roomsModel() const
{
    return rooms;
}
