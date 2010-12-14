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
        int x();
        int y();
        int w();
        int h();
        std::string event();
        void event(std::string event);
        void enabled(bool value);
        bool enabled();
    protected:
    private:
        bool _enabled;
        int _x;
        int _y;
        int _width;
        int _height;
        std::string _event;

};

#endif // AREA_H
