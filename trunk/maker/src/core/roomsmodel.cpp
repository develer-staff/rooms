#include "roomsmodel.h"

#include "core/room.h"

RoomsModel::RoomsModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

Room *RoomsModel::at(int index) const
{
    return rooms.at(index);
}

int RoomsModel::count() const
{
    return rooms.count();
}

int RoomsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return rooms.size();
}

QVariant RoomsModel::data(const QModelIndex &index, int role) const
{
    QVariant result;

    if (!index.isValid())
        return result;

    Room *room = rooms.at(index.row());
    if (!room)
        return result;

    switch (role)
    {
    case Qt::DisplayRole:
        result = room->name();
        break;
    case Qt::DecorationRole:
        result = room->icon();
        break;
    default:
        return result;
    }
    return result;
}

void RoomsModel::appendRoom(const QString &name)
{
    Room *room = new Room(name);

    if (!rooms.contains(room))
    {
        beginInsertRows(QModelIndex(), rooms.size(), rooms.size());
        rooms.append(room);
        endInsertRows();
    }
}

void RoomsModel::setRoomBackground(Room *room, const QPixmap &background)
{
    int i = rooms.indexOf(room);
    if (i == -1)
        return;

    room->setBackground(background);

    emit dataChanged(index(i), index(i));
}

void RoomsModel::addRoomArea(Room *room, const QRect &rect)
{
    int i = rooms.indexOf(room);
    if (i == -1)
        return;

    room->addArea(rect);
}
