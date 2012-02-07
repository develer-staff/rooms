#include "area.h"

Area::Area(const std::string name): id(name)
{

}

Area::~Area()
{

}

void Area::setSize(const float x, const float y, const float width, const float height)
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

bool Area::inside(const float x, const float y) const
{
    float mx = this->x();
    float my = this->y();
    float mw = this->w();
    float mh = this->h();
    return (x >= mx && x <= mx + mw && y >= my && y <= my + mh);
}
