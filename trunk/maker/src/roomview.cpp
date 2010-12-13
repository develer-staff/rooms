#include "roomview.h"

#include <QDebug>

RoomView::RoomView(QWidget *parent) :
    QGraphicsView(parent)
{
    scene = new QGraphicsScene;
    setScene(scene);

    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint &)));
}

void RoomView::showContextMenu(const QPoint &point)
{
    QMenu *menu = new QMenu;
    menu->addAction(tr("Set background"), this, SLOT(setBackground()));
    menu->addSeparator();
    menu->addAction(tr("Add an area"), this, SLOT(addArea()));
    menu->exec(this->mapToGlobal(point));
}

void RoomView::setBackground()
{
    QString bgFile = QFileDialog::getOpenFileName();
    QPixmap bg(bgFile);
    scene->clear();
    scene->addPixmap(bg);
    world->getRoom(activeRoom)->setBackground(bg);
}

void RoomView::setWorld(World *world)
{
    this->world = world;
}
