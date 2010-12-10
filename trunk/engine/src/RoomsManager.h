#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#include <string> //std::string
#include <map> //std::map

class RoomsEngine;
class Room;
class Area;

class RoomsManager
{
    public:
        RoomsManager(RoomsEngine *engine);
        virtual ~RoomsManager();
        Room *addRoom(std::string name, std::string bg);
        Area *addArea(std::string id, std::string room, int x, int y, int w, int h);
        Room *room(std::string name);
        Area *area(std::string name);
        void name(std::string name);
        std::string name();
        void size(int width, int height);
        int height();
        int width();
        Room *currentRoom(std::string id);
        Room *currentRoom();
    protected:
    private:
        RoomsEngine *_engine;
        std::map <std::string, Room *> _rooms;
        std::map <std::string, Area *> _areas;

        std::string _name;
        int _height;
        int _width;
        Room *_current_room;

};

#endif // ROOMMANAGER_H