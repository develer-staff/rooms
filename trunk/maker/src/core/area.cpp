#include "area.h"

Area::Area(const QString &name, const QRect &rect, QObject *parent) :
    QObject(parent)
{
    _name = name;
    _rect = rect;
}

QRect Area::rect() const
{
    return _rect;
}

QString Area::name() const
{
    return _name;
}

void Area::setPos(const QPoint &point)
{
    _rect.translate(point);
}
