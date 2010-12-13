#include "world.h"

World::World(const QString &name, const QSize &size, QObject *parent) :
    QObject(parent)
{
    this->name = name;
    this->size = size;
    rooms = new QVector<Room*>;
}

void World::addRoom(QString const& name)
{
    rooms->append(new Room(name));
}

int World::countRooms() const
{
    return rooms->count();
}

Room *World::getRoom(int index) const
{
    return rooms->at(index);
}

QVector<Room*> *World::getRooms() const
{
    return rooms;
}
