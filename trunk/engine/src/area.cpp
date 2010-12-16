#include "area.h"

Area::Area(const std::string name): id(name)
{
    enabled(true);
}

Area::~Area()
{

}

void Area::size(const int x, const int y, const int width, const int height)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;
}

int Area::x() const
{
    return _x;
}

int Area::y() const
{
    return _y;
}

int Area::h() const
{
    return _height;
}

int Area::w() const
{
    return _width;
}

std::string Area::event() const
{
    return _event;
}

void Area::event(const std::string event)
{
    _event = event;
}

void Area::enabled(const bool value)
{
    _enabled = value;
}


bool Area::enabled() const
{
    return _enabled;
}
