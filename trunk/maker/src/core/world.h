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

    QSize getSize() const;
    RoomsModel *rooms() const;
    QAbstractItemModel *roomsModel() const;

private:
    QString name;
    QSize size;
    RoomsModel *_rooms;
};

#endif // WORLD_H
