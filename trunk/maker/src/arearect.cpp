#include "arearect.h"
#include <QPainter>

AreaRect::AreaRect(Area *area, QGraphicsScene *scene, QGraphicsItem *parent) :
    QGraphicsRectItem(parent, scene)
{
    _area = area;

    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);

    setRect(QRectF(area->rect()));
}

void AreaRect::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsRectItem::mouseReleaseEvent(event);
    _area->setPos(pos().toPoint());
}
