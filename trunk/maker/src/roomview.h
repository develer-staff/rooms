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
    explicit RoomView();
    void setWorld(World *world);

signals:
    void selected(Room *room);
    void selected(Area *area);

public slots:
    void updateRoomView(Room *room);

private slots:
    void setBackground();
    void addArea(const QPoint &pos = QPoint(0, 0), const QSize &size = QSize(64, 64));
    void showContextMenu(const QPoint &point);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    Room *activeRoom() const;

private:
    QPoint last_pos;
    QHash<Room*, QGraphicsScene*> scenes;
    World *_world;
    RoomsModel *rooms;
};

#endif // ROOMVIEW_H
