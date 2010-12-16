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
        Area(const std::string name);
        virtual ~Area();
    public:
        void size(const int x, const int y, const int width, const int height);
        int x() const;
        int y() const;
        int w() const;
        int h() const;
        std::string event() const;
        void event(const std::string event);
        void enabled(const bool value);
        bool enabled() const;
};

#endif // AREA_H
