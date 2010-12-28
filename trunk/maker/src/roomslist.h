#ifndef ROOMSLIST_H
#define ROOMSLIST_H

#include <QListView>
#include "core/world.h"

class RoomsList : public QListView
{
    Q_OBJECT

public:
    explicit RoomsList(World *world, QWidget *parent = 0);
    void setWorld(World *world);

private slots:
    void addRoom();
    void showContextMenu(const QPoint &point);

signals:
    void selected(QModelIndex index);

protected:
    void selectionChanged(const QItemSelection &new_selected, const QItemSelection &old_selected);

private:
    World *_world;

};

#endif // ROOMSLIST_H
