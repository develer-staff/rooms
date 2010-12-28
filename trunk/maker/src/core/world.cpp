#include "world.h"

World::World(const QString &name, const QSize &size, QObject *parent) :
    QObject(parent)
{
    world_name = name;
    world_size = size;
    _rooms = new RoomsModel(this);
}

World::~World()
{
    delete _rooms;
}

QString World::name() const
{
    return world_name;
}

QSize World::size() const
{
    return world_size;
}

void World::setSize(const QSize &size)
{
    world_size = size;
}

RoomsModel *World::rooms() const
{
    return _rooms;
}
