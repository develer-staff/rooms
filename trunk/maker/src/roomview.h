#ifndef ROOMVIEW_H
#define ROOMVIEW_H

#include <QGraphicsView>
#include <QMenu>
#include <QFileDialog>
#include "core/world.h"

class RoomView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit RoomView(QWidget *parent = 0);
    void setWorld(World *world);

signals:
    void selected(Room *room);
    void selected(Area *area);

public slots:
    void setBackground();
    void updateRoomView();

private slots:
    void addArea();
    void showContextMenu(const QPoint &point);

protected:
    void mousePressEvent(QMouseEvent *event);
    Room *activeRoom() const;

private:
    QHash<Room*, QGraphicsScene*> scenes;
    World *_world;
};

#endif // ROOMVIEW_H
