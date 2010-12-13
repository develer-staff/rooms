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

void RoomView::addArea()
{

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
    QString bgFile = QFileDialog::getOpenFileName(this,"Select the background file",
                                                  QDir::currentPath(),
                                                  "Images (*.png *.xpm *.jpg *.gif)");
    QPixmap bg(bgFile);
    bg = bg.scaled(world->getSize());
    scene->clear();
    scene->addPixmap(bg);
    world->getRoom(activeRoom)->setBackground(bg);
}

void RoomView::setWorld(World *world)
{
    this->world = world;
}
