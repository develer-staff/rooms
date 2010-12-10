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
        Room *addRoom(std::string name, std::string bg);
        Room *room(std::string name);
        void name(std::string name);
        std::string name();
        void size(int width, int height);
        int height();
        int width();
    protected:
    private:
        RoomsEngine *_engine;
        std::map <std::string, Room *> _rooms;

        std::string _name;
        int _height;
        int _width;

        bool isUnique(std::string name);

};

#endif // ROOMMANAGER_H
