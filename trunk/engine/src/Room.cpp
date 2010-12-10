#include "Room.h"

Room::Room(std::string name): id(name)
{
    //ctor
}

Room::~Room()
{
    //dtor
}

std::string Room::bg()
{
    return _bg;
}
void Room::bg(std::string id)
{
    _bg = id;
}
