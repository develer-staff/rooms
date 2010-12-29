#include "roomsmodel.h"

RoomsModel::RoomsModel(QObject *parent) :
    QAbstractListModel(parent)
{
    room_count = 0;
    active_room = 0;
}

void RoomsModel::setActiveRoom(Room *room)
{
    active_room = room;
    emit activeRoomChanged();
}

Room *RoomsModel::activeRoom() const
{
    return active_room;
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

Room *RoomsModel::appendRoom()
{
    QString name;

    do
    {
        name.setNum(room_count++);
        name.insert(0, "Room ");
    }
    while (roomExists(name));

    Room *room = new Room(name);
    connect(room, SIGNAL(changed()), this, SLOT(onDataChanged()));

    beginInsertRows(QModelIndex(), rooms.size(), rooms.size());
    rooms.append(room);
    endInsertRows();

    setActiveRoom(room);

    return room;
}

bool RoomsModel::roomExists(const QString &name)
{
    bool exists = false;
    for (int i = 0; i < rooms.count(); i++)
    {
        if (rooms[i]->name() == name)
        {
            exists = true;
            break;
        }
    }
    return exists;
}

void RoomsModel::onDataChanged()
{
    Room *room = (Room *)sender();
    int i = rooms.indexOf(room);

    if (i == -1)
        return;

    emit dataChanged(index(i), index(i));
}
