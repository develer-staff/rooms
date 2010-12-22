#include "roomsmanager.h"
#include "engine.h"
#include "room.h"
#include "item.h"
#include "area.h"

template <class T> void std::freeElements(std::map<string , T *> &container)
{
    for (typename std::map<string, T *>::iterator i = container.begin();
         i != container.end(); ++i)
    {
        logger.write("Garbage collector: " + i->second->id, Log::NOTE);
        delete i->second;
    }
    container.clear();
}

template <class T> T *std::getElement(string name, std::map<string, T *> container)
{
    typename std::map<string, T *>::iterator i = container.find(name);
    if (i == container.end())
        return 0;
    else
        return i->second;
}

RoomsManager::RoomsManager()
{
    current_room = 0;
}

RoomsManager::~RoomsManager()
{
    std::freeElements(rooms);
    std::freeElements(items);
}

void RoomsManager::name(const string name)
{
    _name = name;
}

string RoomsManager::name() const
{
    return _name;
}

void RoomsManager::size(const int width, const int height)
{
    height > 10 ? _height = height : _height = 10;
    width > 10 ? _width = width : _width = 10;
}

int RoomsManager::width() const
{
    return _width;
}

int RoomsManager::height() const
{
    return _height;
}

Room * RoomsManager::addRoom(const string name, const string bg)
{
    Room *r = new Room(name);
    r->bg(bg);
    rooms[name] = r;
    return r;
}

Area * RoomsManager::addArea(const string name, const string room, const int x, const int y,
                             const int w, const int h, const string event)
{
    Area *a = this->room(room)->addArea(name);
    a->size(x, y, w, h);
    a->event(event);
    return a;
}

Item * RoomsManager::addItem(const string name, const string room, const int x, const int y,
                             const int w, const int h, const string event, const string image)
{
    Item *i = new Item(name);
    items[name] = i;
    i->size(x, y, w, h);
    i->event(event);
    i->move(room);
    rooms[room]->addItem(name, i);
    i->image(image);
    return i;
}

void RoomsManager::moveItem(const string name, const string dest)
{
    Item *mov_item = item(name);
    if (mov_item != 0)
    {
        string parent = mov_item->parent();
        Room *r_parent = room(parent);
        Room *r_dest = room(dest);
        if (r_parent == 0 || r_dest == 0)
        {
            logger.write("WARNING: invalid item movement!", Log::WARNING);
            return;
        }
        r_parent->remItem(name);
        mov_item->move(dest);
        r_dest->addItem(name, mov_item);
    }
}

Room * RoomsManager::room(const string name)
{
    return std::getElement(name, rooms);
}

Area * RoomsManager::area(const string name)
{
    return current_room->area(name);
}

Item * RoomsManager::item(const string name)
{
    return std::getElement(name, items);
}

void RoomsManager::currentRoom(const string name)
{
    current_room = room(name);
}

Room *RoomsManager::currentRoom()
{
    return current_room;
}

string RoomsManager::eventAt(const int x, const int y)
{
    return current_room->eventAt(x, y);
}

bool RoomsManager::checkItemPlace(const std::vector <std::pair <string, string> > reqs)
{
    for (std::vector <std::pair <string, string> >::const_iterator i = reqs.begin();
         i != reqs.end(); ++i)
    {
        if (item(i->first)->parent() != i->second)
            return false;
    }
    return true;
}

