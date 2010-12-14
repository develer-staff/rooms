#ifndef ROOMVIEW_H
#define ROOMVIEW_H

#include <QGraphicsView>
#include <QMenu>
#include <QFileDialog>
#include <QVector>
#include "core/world.h"

class RoomView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit RoomView(QWidget *parent = 0);
    void setWorld(World *world);
    void updateRoomView();

private slots:
    void addArea();
    void setBackground();
    void showContextMenu(const QPoint &point);
    void changeActiveRoom(QModelIndex index);

private:
    QGraphicsScene *scene;
    World *world;
    int active_room;
};

#endif // ROOMVIEW_H
