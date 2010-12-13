#include "room.h"

Room::Room(QString const& name, QObject *parent) :
    QObject(parent)
{
    this->name = name;
    areas = new QVector<Area*>;
}

Room::~Room()
{
}

bool Room::addArea(const QPoint &p1, const QPoint &p2)
{
    bool ok;
    Area *area;
    ok = (area = new Area(this, p1, p2));

    if (ok) areas->append(area);

    return ok;
}

void Room::setBackgroundFile(const QString &backgroundFile)
{
    this->backgroundFile = backgroundFile;
}
