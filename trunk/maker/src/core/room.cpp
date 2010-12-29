#include "room.h"

Room::Room(QString const& name, QObject *parent) :
    QObject(parent)
{
    _name = name;
    _icon = QPixmap(QSize(64,64));
    _icon.fill();
    area_count = 0;
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

    return area;
}

void Room::setBackground(const QPixmap &background)
{
    if (!background.isNull())
    {
        _background = background;
        _icon = _background.scaled(QSize(64, 64));
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
