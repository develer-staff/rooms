#include "RoomsManager.h"
#include "RoomsEngine.h"
#include "Room.h"

RoomsManager::RoomsManager(RoomsEngine *engine)
{
    //ctor
    _engine = engine;
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
    if (!isUnique(id))
        return 0;
    Room *r = new Room(id);
    r->bg(bg);
    _rooms[id] = r;
    return r;
}

Room * RoomsManager::room(std::string name)
{
    std::map<std::string, Room *>::iterator i = _rooms.find(name);
    if (i == _rooms.end())
        return 0;
    else
        return i->second;
}

bool RoomsManager::isUnique(std::string name)
{
    if (room(name) == 0)
        return true;
    else
        return false;
}
