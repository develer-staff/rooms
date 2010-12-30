#include "room.h"

Room::Room(const QString &name)
{
    _name = name;
    _icon = QPixmap(QSize(50, 50));
    _icon.fill();
    area_count = 0;
    active_area = 0;
}

Area *Room::addArea(const QPoint &pos, const QSize &size)
{
    QString name;

    do
    {
        name.setNum(area_count++);
        name.insert(0, "Area ");
    }
    while (areaExists(name));

    Area *area = new Area(name, pos, size);
    _areas.append(area);

    setActiveArea(area);

    return area;
}

void Room::setActiveArea(Area *area)
{
    active_area = area;
    emit activeAreaChanged();
}

Area *Room::activeArea() const
{
    return active_area;
}

void Room::setBackground(const QPixmap &background)
{
    if (!background.isNull())
    {
        _background = background;
        _icon = _background.scaled(_icon.size());
        emit changed();
    }
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
    emit changed();
}

QString Room::name() const
{
    return _name;
}

QList<Area*> Room::areas() const
{
    return _areas;
}

bool Room::areaExists(const QString &name)
{
    bool exists = false;

    for (int i = 0; i < _areas.count(); i++)
    {
        if (_areas[i]->name() == name)
        {
            exists = true;
            break;
        }
    }

    return exists;
}
