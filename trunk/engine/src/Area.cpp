#include "Area.h"

Area::Area(std::string name): id(name)
{
    //ctor
}

Area::~Area()
{
    //dtor
}

void Area::size(int x, int y, int width, int height)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;
}
