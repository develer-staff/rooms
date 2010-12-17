#include "roomsmanager.h"
#include "engine.h"
#include "room.h"
#include "item.h"
#include "area.h"


RoomsManager::RoomsManager(Engine *eng)
{
    engine = eng;
    current_room = 0;
}

RoomsManager::~RoomsManager()
{
    for (std::map<string, Room *>::iterator i = rooms.begin();
         i != rooms.end(); ++i)
    {
        engine->log ("DELETING: room " + i->second->id, 3);
        delete i->second;
    }
    rooms.clear();

    for (std::map<string, Item *>::iterator i = items.begin();
         i != items.end(); ++i)
    {
        engine->log ("DELETING: item " + i->second->id, 3);
        delete i->second;
    }
    items.clear();

    for (std::map<string, Area *>::iterator i = areas.begin();
         i != areas.end(); ++i)
    {
        engine->log ("DELETING: area " + i->second->id, 3);
        delete i->second;
    }
    areas.clear();
}

void RoomsManager::name(const string name)
{
    _name = name;
}

string RoomsManager::name() const
{
    return _name;
}

void RoomsManager::size(const int width, const int height)
{
    height > 10 ? _height = height : _height = 10;
    width > 10 ? _width = width : _width = 10;
}

int RoomsManager::width() const
{
    return _width;
}

int RoomsManager::height() const
{
    return _height;
}

Room * RoomsManager::addRoom(const string name, const string bg)
{
    if (room(name) != 0)
        return 0;
    else
    {
        Room *r = new Room(name);
        r->bg(bg);
        rooms[name] = r;
        return r;
    }
}

Area * RoomsManager::addArea(const string name, const string room, const int x, const int y,
                             const int w, const int h, const string event)
{
    if (area(name) != 0)
        return 0;
    else
    {
        Area *a = new Area(name);
        areas[name] = a;
        a->size(x, y, w, h);
        a->event(event);
        rooms[room]->addArea(name, a);
        return a;
    }
}

Item * RoomsManager::addItem(const string name, const string room, const int x, const int y,
                             const int w, const int h, const string event, const string image)
{
    if (item(name) != 0)
        return 0;
    else
    {
        Item *i = new Item(name);
        items[name] = i;
        i->size(x, y, w, h);
        i->event(event);
        i->move(room);
        rooms[room]->addItem(name, i);
        i->image(image);
        return i;
    }
}

void RoomsManager::moveItem(const string name, const string dest)
{
    Item *mov_item = item(name);
    if (mov_item != 0)
    {
        string parent = mov_item->parent();
        Room *r_parent = room(parent);
        Room *r_dest = room(dest);
        if (r_parent == 0 || r_dest == 0)
        {
            engine->log("WARNING: invalid item movement!", 2);
            return;
        }
        r_parent->remItem(name);
        mov_item->move(dest);
        r_dest->addItem(name, mov_item);
    }
}

Room * RoomsManager::room(const string name)
{
    std::map<string, Room *>::iterator i = rooms.find(name);
    if (i == rooms.end())
        return 0;
    else
        return i->second;
}

Area * RoomsManager::area(const string name)
{
    std::map<string, Area *>::iterator i = areas.find(name);
    if (i == areas.end())
        return 0;
    else
        return i->second;
}

Item * RoomsManager::item(const string name)
{
    std::map<string, Item *>::iterator i = items.find(name);
    if (i == items.end())
        return 0;
    else
        return i->second;
}

void RoomsManager::currentRoom(const string name)
{
    current_room = room(name);
}

Room *RoomsManager::currentRoom()
{
    return current_room;
}

string RoomsManager::eventAt(const int x, const int y)
{
    return current_room->eventAt(x, y);
}

bool RoomsManager::checkItemPlace(const std::vector <std::pair <string, string> > reqs)
{
    for (std::vector <std::pair <string, string> >::const_iterator i = reqs.begin();
         i != reqs.end(); ++i)
    {
        if (item(i->first)->parent() != i->second)
            return false;
    }
    return true;
}
