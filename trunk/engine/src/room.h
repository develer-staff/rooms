#ifndef ROOM_H
#define ROOM_H

#include <map> //std::map
#include <string> //string
#include <vector> //std::vector

class Area;
class Item;

using std::string;

/*! \brief Room handler.
 *         Rooms have areas and items references.
 */
class Room
{
    public:
        const string id;
    private:
        string _bg;
        std::map<string, Area *> areas;
        std::map<string, Item *> _items;
    public:
        Room(string name);
        virtual ~Room();
    public:
        string bg();
        void bg(string id);
        Area *addArea(string id, Area *area_ptr);
        Item *addItem(string id, Item *item_ptr);
        void remItem(string id);
        Area *area(string id);
        Item *item(string id);
        std::vector <Item *> items();
        string eventAt(int x, int y);
    protected:
        bool pointInsideArea(int x, int y, Area *area);
};

#endif // ROOM_H
