#ifndef ROOM_H
#define ROOM_H

#include <map>
#include <string>
#include <vector>

class Area;
class Item;

class Room
{
    public:
        Room(std::string name);
        virtual ~Room();
        const std::string id;
        std::string bg();
        void bg(std::string id);
        Area *addArea(std::string id, Area *area_ptr);
        Item *addItem(std::string id, Item *item_ptr);
        void remItem(std::string id);
        Area *area(std::string id);
        Item *item(std::string id);
        std::vector <Item *> items();
        std::string eventAt(int x, int y);
    protected:
    private:
        std::string _bg;
        std::map<std::string, Area *> _areas;
        std::map<std::string, Item *> _items;
        bool pointInsideArea(int x, int y, Area *area);
};

#endif // ROOM_H
