#include "roomsmanager.h"
#include "engine.h"
#include "room.h"
#include "area.h"

RoomsManager::RoomsManager(Engine *engine)
{
    //ctor
    _engine = engine;
    _current_room = 0;
}

RoomsManager::~RoomsManager()
{
    //dtor
    std::map<std::string, Room *>::iterator i;
    for (i = _rooms.begin(); i != _rooms.end(); i++)
    {
        delete i->second;
    }
    _rooms.clear();
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
