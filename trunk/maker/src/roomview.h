#ifndef ROOMVIEW_H
#define ROOMVIEW_H

#include <QGraphicsView>
#include <QMenu>
#include <QFileDialog>

class RoomView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit RoomView(QWidget *parent = 0);

signals:
    void backgroundChanged();
    void cmReq();

public slots:
    void setBackground();
    void showContextMenu(const QPoint &point);
};

#endif // ROOMVIEW_H
