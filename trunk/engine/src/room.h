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
        virtual ~Room();
    public:
        string bg() const;
        void bg(const string id);
        Area *addArea(const string id, Area *area_ptr);
        Item *addItem(const string id, Item *item_ptr);
        void remItem(const string id);
        Area *area(const string id);
        Item *item(const string id);
        std::vector <Item *> items() const;
        string eventAt(const int x, const int y) const;
        Item *itemAt(const int x, const int y);
        Area *areaAt(const int x, const int y);
    protected:
        bool pointInsideArea(const int x, const int y, const Area *area) const;
};

#endif // ROOM_H
