#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#include <string> //std::string
#include <map> //std::map

class RoomsEngine;
class Room;

class RoomsManager
{
    public:
        RoomsManager(RoomsEngine *engine);
        virtual ~RoomsManager();
        Room *addRoom(std::string name);
    protected:
    private:
        RoomsEngine *_engine;
        std::map <std::string, Room *> _rooms;
        bool isUnique(std::string name);
};

#endif // ROOMMANAGER_H
