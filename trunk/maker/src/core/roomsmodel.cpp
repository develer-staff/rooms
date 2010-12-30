#include "roomsmodel.h"

RoomsModel::RoomsModel()
{
    room_count = 0;
    active_room = 0;
}

void RoomsModel::setActiveRoom(Room *room)
{
    active_room = room;
    emit activeRoomChanged(room);
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

    if (index.row() >= rooms.count())
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

int RoomsModel::removeRoom()
{
    int room_index = rooms.indexOf(active_room);
    beginRemoveRows(QModelIndex(), rooms.size(), rooms.size());
    rooms.removeAt(room_index);
    endRemoveRows();
    delete active_room;
    return room_index;
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
