#ifndef WORLD_H
#define WORLD_H

#include "item.h"
#include "roomsmodel.h"

class World
{
public:
    World(const QString &name, const QSize &size);
    ~World();

    void setSize(const QSize &size);
    QSize size() const;

    QString name() const;

    RoomsModel *rooms() const;

private:
    QString world_name;
    QSize world_size;
    RoomsModel *_rooms;
};

#endif // WORLD_H
