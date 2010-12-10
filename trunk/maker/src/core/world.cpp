#include "world.h"

World::World()
{
    rooms = new QVector<Room*>;
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
