#include "roomsmanager.h"
#include "engine.h"
#include "room.h"
#include "item.h"
#include "area.h"


RoomsManager::RoomsManager(Engine *engine)
{
    _engine = engine;
    _current_room = 0;
}

RoomsManager::~RoomsManager()
{
    for (std::map<std::string, Room *>::iterator i = _rooms.begin();
         i != _rooms.end(); i++)
    {
        _engine->log ("DELETING: room " + i->second->id, 3);
        delete i->second;
    }
    _rooms.clear();

    for (std::map<std::string, Item *>::iterator i = _items.begin();
         i != _items.end(); i++)
    {
        _engine->log ("DELETING: item " + i->second->id, 3);
        delete i->second;
    }
    _items.clear();

    for (std::map<std::string, Area *>::iterator i = _areas.begin();
         i != _areas.end(); i++)
    {
        _engine->log ("DELETING: area " + i->second->id, 3);
        delete i->second;
    }
    _areas.clear();
}

void RoomsManager::name(std::string name)
{
    _name = name;
}

std::string RoomsManager::name()
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

Room * RoomsManager::addRoom(std::string id, std::string bg)
{
    if (room(id) != 0)
        return 0;
    else
    {
        Room *r = new Room(id);
        r->bg(bg);
        _rooms[id] = r;
        return r;
    }
}

Area * RoomsManager::addArea(std::string id, std::string room, int x, int y,
                             int w, int h, std::string event)
{
    if (area(id) != 0)
        return 0;
    else
    {
        Area *a = new Area(id);
        _areas[id] = a;
        a->size(x, y, w, h);
        a->event(event);
        _rooms[room]->addArea(id, a);
        return a;
    }
}

Item * RoomsManager::addItem(std::string id, std::string room, int x, int y,
                             int w, int h, std::string event, std::string image)
{
    if (item(id) != 0)
        return 0;
    else
    {
        Item *i = new Item(id);
        _items[id] = i;
        i->size(x, y, w, h);
        i->event(event);
        i->move(room);
        _rooms[room]->addItem(id, i);
        i->image(image);
        return i;
    }
}

void RoomsManager::moveItem(std::string id, std::string dest)
{
    Item *mov_item = item(id);
    if (mov_item != 0)
    {
        std::string parent = mov_item->parent();
        Room *r_parent = _rooms[parent];
        Room *r_dest = _rooms[dest];
        if (r_parent == 0 || r_dest == 0)
        {
            _engine->log("WARNING: invalid item movement!", 2);
            return;
        }
        r_parent->remItem(id);
        mov_item->move(dest);
        r_dest->addItem(id, mov_item);
    }
}

Room * RoomsManager::room(std::string name)
{
    std::map<std::string, Room *>::iterator i = _rooms.find(name);
    if (i == _rooms.end())
        return 0;
    else
        return i->second;
}

Area * RoomsManager::area(std::string name)
{
    std::map<std::string, Area *>::iterator i = _areas.find(name);
    if (i == _areas.end())
        return 0;
    else
        return i->second;
}

Item * RoomsManager::item(std::string name)
{
    std::map<std::string, Item *>::iterator i = _items.find(name);
    if (i == _items.end())
        return 0;
    else
        return i->second;
}

Room *RoomsManager::currentRoom(std::string name)
{
    if (room(name) != 0)
    {
        _current_room = _rooms[name];
        return _current_room;
    } else {
        return 0;
    }
}

Room *RoomsManager::currentRoom()
{
    return _current_room;
}

std::string RoomsManager::eventAt(int x, int y)
{
    return _current_room->eventAt(x, y);
}
