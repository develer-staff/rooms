#include "roomview.h"

RoomView::RoomView(QWidget *parent) :
    QGraphicsView(parent)
{
    scene = new QGraphicsScene;
    setScene(scene);
    active_room = 0;

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
    menu->exec(mapToGlobal(point));
}

void RoomView::setBackground()
{
    QString bgFile = QFileDialog::getOpenFileName(this,"Select the background file",
                                                  QDir::currentPath(),
                                                  "Images (*.png *.xpm *.jpg *.gif)");
    QPixmap bg(bgFile);
    bg = bg.scaled(world->getSize());

    world->rooms()->setRoomBackground(world->rooms()->at(active_room), bg);
    updateRoomView();
}

void RoomView::updateRoomView()
{
    scene->clear();
    scene->addPixmap(world->rooms()->at(active_room)->background());
}

void RoomView::setWorld(World *world)
{
    this->world = world;
}

void RoomView::changeActiveRoom(QModelIndex index)
{
    active_room = index.row();
    updateRoomView();
}
