#include "item.h"

Item::Item(string name): Area(name)
{
    room_parent = "";
}

Item::~Item()
{

}

void Item::move(string room)
{
    room_parent = room;
}

string Item::parent()
{
    return room_parent;
}


void Item::image(string id)
{
    _image = id;
}

string Item::image()
{
    return _image;
}
