#include "Room.h"
#include "Area.h"

Room::Room(std::string name): id(name)
{
    //ctor
}

Room::~Room()
{
    //dtor
    std::map<std::string, Area *>::iterator i;
    for (i = _areas.begin(); i != _areas.end(); i++)
    {
        delete i->second;
    }
    _areas.clear();
}

std::string Room::bg()
{
    return _bg;
}
void Room::bg(std::string id)
{
    _bg = id;
}

Area *Room::addArea(std::string id, Area *area_ptr)
{
    //TODO: a better return check
    if (area(id) == 0)
    {
        _areas[id] = area_ptr;
        return area_ptr;
    } else {
        return 0;
    }
}

Area *Room::area(std::string id)
{
    std::map <std::string, Area *>::iterator i = _areas.find(id);
    if (i ==  _areas.end())
        return 0;
    else
        return i->second;
}

std::string Room::eventAt(int x, int y)
{
    std::map <std::string, Area *>::iterator i;
    for (i = _areas.begin(); i != _areas.end(); i++)
    {
        if (pointInsideArea(x, y, i->second))
            return i->second->event();
    }
    return "";
}

bool Room::pointInsideArea(int x, int y, Area *area)
{
    return (x >= area->x() && x <= area->x() + area->w() && y >= area->y() &&
            y <= area->y() + area->h());
}
