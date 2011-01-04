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
        float _x;
        float _y;
        float _width;
        float _height;
        std::string _event;
    public:
        Area(const std::string name);
        virtual ~Area();
    public:
        void size(const float x, const float y, const float width, const float height);
        float x() const;
        float y() const;
        float w() const;
        float h() const;
        std::string event() const;
        void setEvent(const std::string event);
};

#endif // AREA_H
