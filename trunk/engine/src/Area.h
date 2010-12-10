#ifndef AREA_H
#define AREA_H

#include <string>

class Area
{
    public:
        Area(std::string name);
        virtual ~Area();
        const std::string id;
        void size(int x, int y, int width, int height);
    protected:
    private:
        bool _enabled;
        int _x;
        int _y;
        int _width;
        int _height;

};

#endif // AREA_H
