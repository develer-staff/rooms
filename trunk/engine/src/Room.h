#ifndef ROOM_H
#define ROOM_H

#include <string>

class Room
{
    public:
        Room(std::string name);
        virtual ~Room();
        const std::string id;
        std::string bg();
        void bg(std::string id);
    protected:
    private:
        std::string _bg;
};

#endif // ROOM_H
