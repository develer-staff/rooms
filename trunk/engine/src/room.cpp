#include "room.h"
#include "area.h"
#include "item.h"
#include "engine.h"

Room::Room(const string name): id(name)
{

}

Room::~Room()
{
    for (std::map<string, Area *>::iterator i = areas.begin();
         i != areas.end(); ++i)
        delete i->second;
    areas.clear();
}

string Room::bg() const
{
    return _bg;
}

void Room::bg(const string name)
{
    _bg = name;
}

string Room::bgm() const
{
    return _bgm;
}

void Room::setBgm(const string name)
{
    _bgm = name;
}

Area *Room::addArea(const string name)
{
    Area *a = new Area(name);
    areas[name] = a;
    return a;
}

Item *Room::addItem(const string name, Item *item_ptr)
{
    _items[name] = item_ptr;
    return item_ptr;
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

string Room::eventAt(const float x, const float y) const
{
    for (std::map <string, Item *>::const_iterator i = _items.begin(); i != _items.end(); ++i)
    {
        Area *a = dynamic_cast<Area *>(i->second);
        if (a->inside(x, y))
            return i->second->event();
    }
    for (std::map <string, Area *>::const_iterator i = areas.begin(); i != areas.end(); ++i)
    {
        Area *a = i->second;
        if (a->inside(x, y))
            return i->second->event();
    }
    return "";
}

Item *Room::itemAt(const float x, const float y)
{
    for (std::map <string, Item *>::iterator i = _items.begin(); i != _items.end(); ++i)
    {
        Area *a = dynamic_cast<Area *>(i->second);
        if (a->inside(x, y))
            return i->second;
    }
    return 0;
}

Area *Room::areaAt(const float x, const float y)
{
    for (std::map <string, Area *>::iterator i = areas.begin(); i != areas.end(); ++i)
    {
        Area *a = i->second;
        if (a->inside(x, y))
            return a;
    }
    return 0;
}
