#ifndef WORLD_H
#define WORLD_H

#include <QObject>
#include <QVector>
#include "room.h"
#include "item.h"

class QAbstractItemModel;
class RoomsModel;

class World : public QObject
{
    Q_OBJECT

public:
    World(const QString &name, const QSize &size, QObject *parent = 0);

    void addRoom(QString const& name);
    int countRooms() const;
    Room *getRoom(int index) const;
    QSize getSize() const;
    QAbstractItemModel *roomsModel() const;

private:
    QString name;
    QSize size;
    RoomsModel *rooms;
};

#endif // WORLD_H
