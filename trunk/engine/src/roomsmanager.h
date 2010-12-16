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
        Room *addRoom(const string name, const string bg);
        Area *addArea(const string id, const string room, const int x, const int y,
                      const int w, const int h, const string event);
        Item *addItem(const string id, const string room, const int x, const int y,
                      const int w, const int h, const string event, const string image);
        Room *room(const string name);
        Area *area(const string name);
        Item *item(const string name);
        void name(const string name);
        string name() const;
        void size(const int width, const int height);
        int height() const;
        int width() const;
        Room *currentRoom(const string id);
        Room *currentRoom();
        string eventAt(const int x, const int y);
        void moveItem(const string id, const string dest);
};

#endif // ROOMMANAGER_H
