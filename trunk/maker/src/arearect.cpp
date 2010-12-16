#include "arearect.h"
#include <QPainter>

AreaRect::AreaRect(const Area *area, QGraphicsScene *scene, QGraphicsItem *parent) :
    QGraphicsItem(parent, scene)
{
    pen_width = 2;
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    bounding_rect = QRectF(-10 - pen_width / 2, -10 - pen_width / 2,
                           20 + pen_width, 20 + pen_width);
}

QRectF AreaRect::boundingRect() const
{
    return bounding_rect;
}

void AreaRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::red, pen_width));
    painter->drawRect(-10, -10, 20, 20);
    painter->setOpacity(0.5);
    painter->fillRect(-10, -10, 20, 20, QBrush(Qt::red));
}
