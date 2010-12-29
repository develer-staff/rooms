#ifndef ROOMSMODEL_H
#define ROOMSMODEL_H

#include <QAbstractListModel>
#include "room.h"

class RoomsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit RoomsModel(QObject *parent = 0);
    Room *at(int index) const;
    int count() const;
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    Room *appendRoom();
    bool roomExists(const QString &name);

    Room *activeRoom() const;
    void setActiveRoom(Room *room);

private slots:
    void onDataChanged();

signals:
    void activeRoomChanged();

private:
    QList<Room *> rooms;
    int room_count;
    Room *active_room;
};

#endif // ROOMSMODEL_H
