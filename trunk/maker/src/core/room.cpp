#include "room.h"

Room::Room(QString const& name, QObject *parent) :
    QObject(parent)
{
    this->_name = name;
    areas = new QVector<Area*>;
}

Room::~Room()
{
}

bool Room::addArea(const QRect &rect)
{
    bool ok;
    Area *area;
    ok = (this->_background.rect().contains(rect));

    if (ok)
    {
        area = new Area(rect);
        areas->append(area);
    }

    return ok;
}

void Room::setBackground(const QPixmap &background)
{
    this->_background = background;
}

QPixmap Room::background() const
{
    return _background;
}

QString Room::name() const
{
    return _name;
}
