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

void RoomsManager::name(string name)
{
    _name = name;
}

string RoomsManager::name()
{
    return _name;
}

void RoomsManager::size(int width, int height)
{
    height > 10 ? _height = height : _height = 10;
    width > 10 ? _width = width : _width = 10;
}

int RoomsManager::width()
{
    return _width;
}

int RoomsManager::height()
{
    return _height;
}

Room * RoomsManager::addRoom(string id, string bg)
{
    if (room(id) != 0)
        return 0;
    else
    {
        Room *r = new Room(id);
        r->bg(bg);
        rooms[id] = r;
        return r;
    }
}

Area * RoomsManager::addArea(string id, string room, int x, int y,
                             int w, int h, string event)
{
    if (area(id) != 0)
        return 0;
    else
    {
        Area *a = new Area(id);
        areas[id] = a;
        a->size(x, y, w, h);
        a->event(event);
        rooms[room]->addArea(id, a);
        return a;
    }
}

Item * RoomsManager::addItem(string id, string room, int x, int y,
                             int w, int h, string event, string image)
{
    if (item(id) != 0)
        return 0;
    else
    {
        Item *i = new Item(id);
        items[id] = i;
        i->size(x, y, w, h);
        i->event(event);
        i->move(room);
        rooms[room]->addItem(id, i);
        i->image(image);
        return i;
    }
}

void RoomsManager::moveItem(string id, string dest)
{
    Item *mov_item = item(id);
    if (mov_item != 0)
    {
        string parent = mov_item->parent();
        Room *r_parent = rooms[parent];
        Room *r_dest = rooms[dest];
        if (r_parent == 0 || r_dest == 0)
        {
            engine->log("WARNING: invalid item movement!", 2);
            return;
        }
        r_parent->remItem(id);
        mov_item->move(dest);
        r_dest->addItem(id, mov_item);
    }
}

Room * RoomsManager::room(string name)
{
    std::map<string, Room *>::iterator i = rooms.find(name);
    if (i == rooms.end())
        return 0;
    else
        return i->second;
}

Area * RoomsManager::area(string name)
{
    std::map<string, Area *>::iterator i = areas.find(name);
    if (i == areas.end())
        return 0;
    else
        return i->second;
}

Item * RoomsManager::item(string name)
{
    std::map<string, Item *>::iterator i = items.find(name);
    if (i == items.end())
        return 0;
    else
        return i->second;
}

Room *RoomsManager::currentRoom(string name)
{
    if (room(name) != 0)
    {
        current_room = rooms[name];
        return current_room;
    }
    else
    {
        return 0;
    }
}

Room *RoomsManager::currentRoom()
{
    return current_room;
}

string RoomsManager::eventAt(int x, int y)
{
    return current_room->eventAt(x, y);
}
