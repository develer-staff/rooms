#include "area.h"

Area::Area(const QRect &rect, QObject *parent) :
    QObject(parent)
{
    _rect = rect;
}

QRect Area::rect() const
{
    return _rect;
}
