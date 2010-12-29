#include "roomview.h"
#include "arearect.h"
#include <QMouseEvent>

RoomView::RoomView(QWidget *parent) :
    QGraphicsView(parent)
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setRenderHint(QPainter::Antialiasing);

    setFixedSize(600, 500);

    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint &)));
}

void RoomView::setWorld(World *world)
{
    setDisabled(true);
    _world = world;
    connect(_world->rooms(), SIGNAL(activeRoomChanged()), this, SLOT(updateRoomView()));
    setFixedSize(_world->size());
}

void RoomView::addArea()
{
    updateRoomView();
    activeRoom()->addArea(QPoint(0, 0), QSize(64, 64));
    AreaRect *area_rect = new AreaRect(activeRoom()->areas().last());
    scenes[activeRoom()]->addItem(area_rect);
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
    updateRoomView();
    QString bgFile = QFileDialog::getOpenFileName(this,"Select the background file",
                                                  QDir::currentPath(),
                                                  "Images (*.png *.xpm *.jpg *.gif)");
    QPixmap bg(bgFile);
    if (bg.isNull())
        return;

    bg = bg.scaled(_world->size());

    activeRoom()->setBackground(bg);
    scenes[activeRoom()]->addPixmap(bg);
}

void RoomView::updateRoomView()
{
    setEnabled(true);
    if (!scenes.contains(activeRoom()))
    {
        scenes.insert(activeRoom(),
                      new QGraphicsScene(QRectF(QPoint(0, 0), _world->size())));
        scenes[activeRoom()]->addPixmap(activeRoom()->background());
        for (int i = 0; i < activeRoom()->areas().count(); i++)
        {
            AreaRect *area_rect = new AreaRect(activeRoom()->areas().at(i));
            scenes[activeRoom()]->addItem(area_rect);
        }
    }

    setScene(scenes[activeRoom()]);
    emit selected(activeRoom());
}

Room *RoomView::activeRoom() const
{
    return _world->rooms()->activeRoom();
}

void RoomView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    QGraphicsItem *item = itemAt(event->pos());
    if (item == 0 || item->zValue() == 0)
        emit selected(activeRoom());
    else
        emit selected(((AreaRect *)item)->area());
}
