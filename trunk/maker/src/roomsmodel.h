#ifndef ROOMSMODEL_H
#define ROOMSMODEL_H

#include <QAbstractListModel>
#include <QtContainerFwd>


class Room;


class RoomsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit RoomsModel(QObject *parent = 0);
    Room *at(int index);
    int count();
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    void appendRoom(Room *room);

private:
    QList<Room *> rooms;
};

#endif // ROOMSMODEL_H