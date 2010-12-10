#include "roomview.h"

#include <QDebug>

RoomView::RoomView(QWidget *parent, World *world) :
    QGraphicsView(parent)
{
    this->world = world;
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
    menu->addAction(tr("Add an item"), this, SLOT(setItem()));
    menu->exec(this->mapToGlobal(point));
}

void RoomView::setBackground()
{
    QString bgFile = QFileDialog::getOpenFileName();

    scene->clear();
    scene->addPixmap(QPixmap(bgFile));
}
