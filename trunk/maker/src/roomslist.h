#ifndef ROOMSLIST_H
#define ROOMSLIST_H

#include <QListView>
#include "core/world.h"

class RoomsList : public QListView
{
    Q_OBJECT

public:
    explicit RoomsList();
    void setWorld(World *world);

signals:
    void selected(QModelIndex index);

private slots:
    void addRoom();
    void showContextMenu(const QPoint &point);

protected:
    void selectionChanged(const QItemSelection &new_selected, const QItemSelection &old_selected);

private:
    World *_world;
    RoomsModel *rooms;

};

#endif // ROOMSLIST_H
