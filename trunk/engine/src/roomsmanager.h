#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#include <string> //string
#include <map> //std::map

class Engine;
class Room;
class Area;
class Item;

using std::string;

/*! \brief Rooms interface.
 *         Safely creates and garbage-collects rooms, areas and items.
 */
class RoomsManager
{
    private:
        Engine *engine;
        std::map <string, Room *> rooms;
        std::map <string, Area *> areas;
        std::map <string, Item *> items;
        string _name;
        int _height;
        int _width;
        Room *current_room;
    public:
        RoomsManager(Engine *eng);
        virtual ~RoomsManager();
    public:
        Room *addRoom(string name, string bg);
        Area *addArea(string id, string room, int x, int y,
                      int w, int h, string event);
        Item *addItem(string id, string room, int x, int y,
                      int w, int h, string event, string image);
        Room *room(string name);
        Area *area(string name);
        Item *item(string name);
        void name(string name);
        string name();
        void size(int width, int height);
        int height();
        int width();
        Room *currentRoom(string id);
        Room *currentRoom();
        string eventAt(int x, int y);
        void moveItem(string id, string dest);
};

#endif // ROOMMANAGER_H
