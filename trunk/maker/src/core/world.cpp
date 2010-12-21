#include "world.h"

World::World(const QString &name, const QSize &size, QObject *parent) :
    QObject(parent)
{
    this->name = name;
    this->_size = size;
    _rooms = new RoomsModel(this);
}

QSize World::size() const
{
    return _size;
}

void World::setSize(const QSize &size)
{
    _size = size;
}

RoomsModel *World::rooms() const
{
    return _rooms;
}
