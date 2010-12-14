#include "item.h"

Item::Item(std::string name): Area(name)
{
    _room_parent = "";
}

Item::~Item()
{

}

void Item::move(std::string room)
{
    _room_parent = room;
}

std::string Item::parent()
{
    return _room_parent;
}


void Item::image(std::string id)
{
    _image = id;
}

std::string Item::image()
{
    return _image;
}
