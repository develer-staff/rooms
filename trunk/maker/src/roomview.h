#ifndef ROOMVIEW_H
#define ROOMVIEW_H

#include <QGraphicsView>
#include <QMenu>
#include <QFileDialog>
#include <QVector>

class RoomView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit RoomView(QWidget *parent = 0);

signals:
    void backgroundChanged();

public slots:
    void setBackground();
    void showContextMenu(const QPoint &point);

private:
    QGraphicsScene *scene;
    QVector<Room*> rooms;
    int activeRoom;
};

#endif // ROOMVIEW_H
