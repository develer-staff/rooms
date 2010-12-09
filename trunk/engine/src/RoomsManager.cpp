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

Room * RoomsManager::addRoom(std::string id)
{
    if (!isUnique(id))
        return 0;
    Room *r = new Room(id);
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
