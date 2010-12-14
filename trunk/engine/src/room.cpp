#include "room.h"
#include "area.h"
#include "item.h"

Room::Room(string name): id(name)
{

}

Room::~Room()
{

}

string Room::bg()
{
    return _bg;
}
void Room::bg(string id)
{
    _bg = id;
}

Area *Room::addArea(string id, Area *area_ptr)
{
    //TODO: a better return check
    if (area(id) == 0)
    {
        areas[id] = area_ptr;
        return area_ptr;
    } else {
        return 0;
    }
}

Item *Room::addItem(string id, Item *item_ptr)
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

void Room::remItem(string id)
{
    _items.erase(id);
}

Area *Room::area(string id)
{
    std::map <string, Area *>::iterator i = areas.find(id);
    if (i ==  areas.end())
        return 0;
    else
        return i->second;
}

Item *Room::item(string id)
{
    std::map <string, Item *>::iterator i = _items.find(id);
    if (i ==  _items.end())
        return 0;
    else
        return i->second;
}

std::vector<Item *> Room::items()
{
    std::vector<Item *> r;
    for (std::map<string, Item *>::iterator i = _items.begin();
         i != _items.end(); ++i)
        r.push_back(i->second);
    return r;
}

string Room::eventAt(int x, int y)
{
    for (std::map <string, Item *>::iterator i = _items.begin(); i != _items.end(); ++i)
    {
        if (pointInsideArea(x, y, dynamic_cast<Area *>(i->second)))
            return i->second->event();
    }
    for (std::map <string, Area *>::iterator i = areas.begin(); i != areas.end(); ++i)
    {
        if (pointInsideArea(x, y, i->second) && i->second->enabled())
            return i->second->event();
    }
    return "";
}

bool Room::pointInsideArea(int x, int y, Area *area)
{
    return (x >= area->x() && x <= area->x() + area->w() && y >= area->y() &&
            y <= area->y() + area->h());
}
