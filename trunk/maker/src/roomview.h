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
    explicit RoomView(QWidget *parent = 0, World *world = 0);

public slots:
    void setBackground();
    void showContextMenu(const QPoint &point);

private:
    QGraphicsScene *scene;
    World *world;
    int activeRoom;
};

#endif // ROOMVIEW_H
