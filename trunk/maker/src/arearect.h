#ifndef AREAWIDGET_H
#define AREAWIDGET_H

#include <QGraphicsItem>
#include "core/area.h"

class AreaRect : public QGraphicsItem
{

public:
    explicit AreaRect(const Area *area, QGraphicsScene *scene = 0, QGraphicsItem *parent = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

private:
    QRectF bounding_rect;
    qreal pen_width;
    Area *_area;
};

#endif // AREAWIDGET_H
