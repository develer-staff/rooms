#include "roomview.h"

RoomView::RoomView(QWidget *parent) :
    QGraphicsView(parent)
{
    emit cmReq();
    this->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));");
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
