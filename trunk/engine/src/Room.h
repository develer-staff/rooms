#ifndef ROOM_H
#define ROOM_H

#include <map>
#include <string>

class Area;

class Room
{
    public:
        Room(std::string name);
        virtual ~Room();
        const std::string id;
        std::string bg();
        void bg(std::string id);
        Area *addArea(std::string id, Area *area_ptr);
        Area *area(std::string id);
    protected:
    private:
        std::string _bg;
        std::map<std::string, Area *> _areas;
};

#endif // ROOM_H
