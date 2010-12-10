#include "roomview.h"

#include <QDebug>

RoomView::RoomView(QWidget *parent) :
    QGraphicsView(parent)
{
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint &)));
}

void RoomView::showContextMenu(const QPoint &point)
{
    QMenu *menu = new QMenu;
    menu->addAction(tr("Set background"), this, SLOT(setBackground()));
    menu->addAction(tr("Add an area"), this, SLOT(addArea()));
    menu->addAction(tr("Add an item"), this, SLOT(setItem()));
    menu->exec(this->mapToGlobal(point));
}

void RoomView::setBackground()
{
    QString bgFile;
    QPalette palette;

    bgFile = QFileDialog::getOpenFileName();
    palette.setBrush(this->backgroundRole(), QBrush(QImage(bgFile)));

    this->setPalette(palette);
}
