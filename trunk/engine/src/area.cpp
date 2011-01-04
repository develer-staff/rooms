#include "area.h"

Area::Area(const std::string name): id(name)
{

}

Area::~Area()
{

}

void Area::size(const float x, const float y, const float width, const float height)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;
}

float Area::x() const
{
    return _x;
}

float Area::y() const
{
    return _y;
}

float Area::h() const
{
    return _height;
}

float Area::w() const
{
    return _width;
}

std::string Area::event() const
{
    return _event;
}

void Area::setEvent(const std::string event)
{
    _event = event;
}
