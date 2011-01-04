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
        Room(const string name);
        ~Room();
    public:
        string bg() const;
        void bg(const string name);
        Area *addArea(const string name);
        Item *addItem(const string name, Item *item_ptr);
        void remItem(const string name);
        Area *area(const string name);
        Item *item(const string name);
        std::vector <Item *> items() const;
        string eventAt(const float x, const float y) const;
        Item *itemAt(const float x, const float y);
        Area *areaAt(const float x, const float y);
    protected:
        bool pointInsideArea(const float x, const float y, const Area *area) const;
};

#endif // ROOM_H
