#ifndef WORLD_H
#define WORLD_H

#include <QObject>
#include <QVector>
#include "room.h"
#include "item.h"
#include "roomsmodel.h"

class QAbstractItemModel;
class RoomsModel;

class World : public QObject
{
    Q_OBJECT

public:
    World(const QString &name, const QSize &size, QObject *parent = 0);

    void setSize(const QSize &size);
    QSize size() const;
    RoomsModel *rooms() const;

private:
    QString name;
    QSize _size;
    RoomsModel *_rooms;
};

#endif // WORLD_H
