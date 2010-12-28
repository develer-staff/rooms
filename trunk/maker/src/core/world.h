#ifndef WORLD_H
#define WORLD_H

#include <QObject>
#include "item.h"
#include "roomsmodel.h"

class QAbstractItemModel;
class RoomsModel;

class World : public QObject
{
    Q_OBJECT

public:
    World(const QString &name, const QSize &size, QObject *parent = 0);
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
