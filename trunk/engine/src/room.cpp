#include "room.h"
#include "area.h"
#include "item.h"

Room::Room(std::string name): id(name)
{

}

Room::~Room()
{

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

Item *Room::addItem(std::string id, Item *item_ptr)
{
    //TODO: a better return check
    if (item(id) == 0)
    {
        _items[id] = item_ptr;
        return item_ptr;
    } else {
        return 0;
    }
}

void Room::remItem(std::string id)
{
    _items.erase(id);
}

Area *Room::area(std::string id)
{
    std::map <std::string, Area *>::iterator i = _areas.find(id);
    if (i ==  _areas.end())
        return 0;
    else
        return i->second;
}

Item *Room::item(std::string id)
{
    std::map <std::string, Item *>::iterator i = _items.find(id);
    if (i ==  _items.end())
        return 0;
    else
        return i->second;
}

std::vector<Item *> Room::items()
{
    std::vector<Item *> r;
    for (std::map<std::string, Item *>::iterator i = _items.begin();
         i != _items.end(); i++)
        r.push_back(i->second);
    return r;
}

std::string Room::eventAt(int x, int y)
{
    for (std::map <std::string, Item *>::iterator i = _items.begin(); i != _items.end(); i++)
    {
        if (pointInsideArea(x, y, dynamic_cast<Area *>(i->second)))
            return i->second->event();
    }
    for (std::map <std::string, Area *>::iterator i = _areas.begin(); i != _areas.end(); i++)
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
