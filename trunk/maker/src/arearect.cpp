#include "arearect.h"

AreaRect::AreaRect(Area *area)
{
    _area = area;

    setZValue(1);

    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);

    setRect(area->rect());
    setPos(area->pos());
}

void AreaRect::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsRectItem::mouseReleaseEvent(event);
    _area->setPos(pos().toPoint());
}

Area *AreaRect::area() const
{
    return _area;
}
