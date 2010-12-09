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
}

Room * RoomsManager::addRoom(std::string id)
{
    if (!isUnique(id))
        return 0;
    _rooms[id] = new Room(id);
}

bool RoomsManager::isUnique(std::string name)
{
    if (_rooms.find(name) == _rooms.end())
        return true;
    else
        return false;
}
