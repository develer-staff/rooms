#include "world.h"

World::World(const QString &name, const QSize &size, QObject *parent) :
    QObject(parent)
{
    this->name = name;
    this->size = size;
    _rooms = new RoomsModel(this);
}

QSize World::getSize() const
{
    return size;
}

RoomsModel *World::rooms() const
{
    return _rooms;
}
