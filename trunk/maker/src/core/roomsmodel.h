#ifndef ROOMSMODEL_H
#define ROOMSMODEL_H

#include <QAbstractListModel>


class Room;


class RoomsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit RoomsModel(QObject *parent = 0);
    Room *at(int index) const;
    int count() const;
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    void appendRoom();

    void addRoomArea(Room *room, const QRect &rect);

    bool areaExists(const QString &name);
    bool roomExists(const QString &name);

private slots:
    void onDataChanged();

private:
    QList<Room *> rooms;
    int area_count;
    int room_count;
};

#endif // ROOMSMODEL_H
