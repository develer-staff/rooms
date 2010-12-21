#include "room.h"

Room::Room(QString const& name, QObject *parent) :
    QObject(parent)
{
    this->_name = name;
    _icon = QPixmap(QSize(64,64));
    _icon.fill();
}

Room::~Room()
{
}

void Room::addArea(const QString &name, const QRect &rect)
{
    _areas.append(new Area(name, rect));
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

void Room::setName(const QString &name)
{
    _name = name;
}

QString Room::name() const
{
    return _name;
}

QList<Area*> Room::areas() const
{
    return _areas;
}
