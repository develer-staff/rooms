#include "room.h"

Room::Room(QString const& name, QObject *parent) :
    QObject(parent)
{
    this->name = name;
}

Room::~Room()
{
}

void Room::setBackgroundFile(const QString &backgroundFile)
{
    this->backgroundFile = backgroundFile;
}
