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

signals:
    void roomChanged(Room *room);
    void selected(Room *room);
    void selected(Area *area);

public slots:
    void setBackground();

private slots:
    void addArea();
    void showContextMenu(const QPoint &point);
    void changeActiveRoom(QModelIndex index);

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    QHash<Room*, QGraphicsScene*> scenes;
    World *world;
    Room *active_room;
};

#endif // ROOMVIEW_H
