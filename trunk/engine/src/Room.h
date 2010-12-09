#ifndef ROOM_H
#define ROOM_H

#include <string>

class Room
{
    public:
        Room(std::string name);
        virtual ~Room();
        const std::string id;
    protected:
    private:
};

#endif // ROOM_H
