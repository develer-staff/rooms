#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#include <string> //std::string
#include <map> //std::map

class Engine;
class Room;
class Area;
class Item;

class RoomsManager
{
    public:
        RoomsManager(Engine *engine);
        virtual ~RoomsManager();
        Room *addRoom(std::string name, std::string bg);
        Area *addArea(std::string id, std::string room, int x, int y,
                      int w, int h, std::string event);
        Item *addItem(std::string id, std::string room, int x, int y,
                      int w, int h, std::string event, std::string image);
        Room *room(std::string name);
        Area *area(std::string name);
        Item *item(std::string name);
        void name(std::string name);
        std::string name();
        void size(int width, int height);
        int height();
        int width();
        Room *currentRoom(std::string id);
        Room *currentRoom();
        std::string eventAt(int x, int y);
        void moveItem(std::string id, std::string dest);
    protected:
    private:
        Engine *_engine;
        std::map <std::string, Room *> _rooms;
        std::map <std::string, Area *> _areas;
        std::map <std::string, Item *> _items;

        std::string _name;
        int _height;
        int _width;
        Room *_current_room;

};

#endif // ROOMMANAGER_H
