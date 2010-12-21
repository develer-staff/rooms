#include "room.h"
#include "area.h"
#include "item.h"

Room::Room(const string name): id(name)
{

}

Room::~Room()
{

}

string Room::bg() const
{
    return _bg;
}
void Room::bg(const string name)
{
    _bg = name;
}

Area *Room::addArea(const string name, Area *area_ptr)
{
    //TODO: a better return check
    if (area(name) == 0)
    {
        areas[name] = area_ptr;
        return area_ptr;
    }
    else
    {
        return 0;
    }
}

Item *Room::addItem(const string name, Item *item_ptr)
{
    //TODO: a better return check
    if (item(name) == 0)
    {
        _items[name] = item_ptr;
        return item_ptr;
    }
    else
    {
        return 0;
    }
}

void Room::remItem(const string name)
{
    _items.erase(name);
}

Area *Room::area(const string name)
{
    std::map <string, Area *>::const_iterator i = areas.find(name);
    if (i ==  areas.end())
        return 0;
    else
        return i->second;
}

Item *Room::item(const string name)
{
    std::map <string, Item *>::const_iterator i = _items.find(name);
    if (i ==  _items.end())
        return 0;
    else
        return i->second;
}

std::vector<Item *> Room::items() const
{
    std::vector<Item *> r;
    for (std::map<string, Item *>::const_iterator i = _items.begin();
         i != _items.end(); ++i)
        r.push_back(i->second);
    return r;
}

string Room::eventAt(const int x, const int y) const
{
    for (std::map <string, Item *>::const_iterator i = _items.begin(); i != _items.end(); ++i)
    {
        if (pointInsideArea(x, y, dynamic_cast<Area *>(i->second)))
            return i->second->event();
    }
    for (std::map <string, Area *>::const_iterator i = areas.begin(); i != areas.end(); ++i)
    {
        if (pointInsideArea(x, y, i->second) && i->second->enabled())
            return i->second->event();
    }
    return "";
}

Item *Room::itemAt(const int x, const int y)
{
    for (std::map <string, Item *>::iterator i = _items.begin(); i != _items.end(); ++i)
        if (pointInsideArea(x, y, dynamic_cast<Area *>(i->second)))
            return i->second;
    return 0;
}

Area *Room::areaAt(const int x, const int y)
{
    for (std::map <string, Area *>::iterator i = areas.begin(); i != areas.end(); ++i)
        if (pointInsideArea(x, y, i->second))
            return i->second;
    return 0;
}

bool Room::pointInsideArea(const int x, const int y, const Area *area) const
{
    return (x >= area->x() && x <= area->x() + area->w() && y >= area->y() &&
            y <= area->y() + area->h());
}
