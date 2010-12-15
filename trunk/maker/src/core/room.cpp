#include "room.h"

Room::Room(QString const& name, QObject *parent) :
    QObject(parent)
{
    this->_name = name;
    _areas = new QList<Area*>;
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
        _areas->append(area);
    }

    return ok;
}

void Room::setBackground(const QPixmap &background)
{
    _background = background;
    _icon = _background.scaled(QSize(64, 64));
}

QPixmap Room::background() const
{
    return _background;
}

QPixmap Room::icon() const
{
    return _icon;
}

QString Room::name() const
{
    return _name;
}

QList<Area*> *Room::areas() const
{
    return _areas;
}
