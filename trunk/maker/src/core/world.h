#ifndef WORLD_H
#define WORLD_H

#include <QVector>
#include "room.h"
#include "item.h"

class World : public QObject
{
    Q_OBJECT

public:
    World(const QString &name, const QRect &rect, QObject *parent = 0);

    void addRoom(QString const& name);
    int countRooms() const;
    Room *getRoom(int index) const;
    QVector<Room*> *getRooms() const;

private:
    QVector<Room*> *rooms;
};

#endif // WORLD_H
