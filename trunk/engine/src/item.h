#ifndef ITEM_H
#define ITEM_H

#include <string>

#include "area.h"

class Item: public Area
{
    public:
        Item(std::string name);
        virtual ~Item();
        void move(std::string room);
        std::string parent();
        void image(std::string id);
        std::string image();
    protected:
    private:
        std::string _room_parent;
        std::string _image;
};

#endif // ITEM_H
