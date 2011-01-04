#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#define ROOM_INV "!INVENTORY"
#define ROOM_NOWHERE "!NOWHERE"

#include <string> //string
#include <map> //std::map
#include <vector> //std::vector

class Room;
class Area;
class Item;

using std::string;


namespace utils
{
    template <class T> void freeElements(std::map<string , T *> &container);
    template <class T> T *getElement(string name, std::map<string, T *> container);
}

/*! \brief Rooms interface.
 *         Safely creates and garbage-collects rooms, areas and items.
 */
class RoomsManager
{
    private:
        std::map <string, Room *> rooms;
        std::map <string, Item *> items;
        string _name;
        int _height;
        int _width;
        Room *current_room;
    public:
        RoomsManager();
        ~RoomsManager();
    public:
        Room *addRoom(const string name, const string bg);
        Area *addArea(const string name, const string room, const float x, const float y,
                      const float w, const float h, const string event);
        Item *addItem(const string name, const string room, const float x, const float y,
                      const float w, const float h, const string event, const string image);
        Room *room(const string name);
        Area *area(const string name);
        Item *item(const string name);
        void name(const string name);
        string name() const;
        void size(const int width, const int height);
        int height() const;
        int width() const;
        void setCurrentRoom(const string name);
        Room *currentRoom();
        string eventAt(const float x, const float y);
        void moveItem(const string name, const string dest);
        bool checkItemPlace(const std::vector <std::pair <string, string> > reqs);
};



#endif // ROOMMANAGER_H
