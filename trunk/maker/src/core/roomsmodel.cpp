#include "roomsmodel.h"

#include "core/room.h"

RoomsModel::RoomsModel(QObject *parent) :
    QAbstractListModel(parent)
{
    room_count = 0;
    area_count = 0;
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

void RoomsModel::appendRoom()
{
    QString name;

    do
    {
        name.setNum(room_count++);
        name.insert(0, "Room ");
    }
    while (roomExists(name));

    Room *room = new Room(name);

    beginInsertRows(QModelIndex(), rooms.size(), rooms.size());
    rooms.append(room);
    endInsertRows();
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
    QString name;
    int i = rooms.indexOf(room);
    if (i == -1)
        return;

    do
    {
        name.setNum(area_count++);
        name.insert(0, "Area ");
    }
    while (areaExists(name));

    room->addArea(name, rect);
}

bool RoomsModel::areaExists(const QString &name)
{
    bool exists = false;
    for (int i = 0; i < rooms.count(); i++)
    {
        for (int j = 0; j < rooms[i]->areas().count(); j++)
        {
            if (rooms[i]->areas().at(j)->name() == name)
            {
                exists = true;
                break;
            }
        }
    }
    return exists;
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
