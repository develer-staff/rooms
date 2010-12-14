#ifndef AREA_H
#define AREA_H

#include <string> //std::string

/*! \brief Area main handler.
 *         Rectangular interactive area inside a room.
 */
class Area
{
    public:
        const std::string id;
    protected:
        bool _enabled;
        int _x;
        int _y;
        int _width;
        int _height;
        std::string _event;
    public:
        Area(std::string name);
        virtual ~Area();
    public:
        void size(int x, int y, int width, int height);
        int x();
        int y();
        int w();
        int h();
        std::string event();
        void event(std::string event);
        void enabled(bool value);
        bool enabled();
};

#endif // AREA_H
