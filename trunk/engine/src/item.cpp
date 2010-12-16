#include "item.h"

Item::Item(const string name): Area(name)
{
    room_parent = "";
}

Item::~Item()
{

}

void Item::move(const string room)
{
    room_parent = room;
}

string Item::parent() const
{
    return room_parent;
}


void Item::image(const string id)
{
    _image = id;
}

string Item::image() const
{
    return _image;
}
