#ifndef ITEM_H
#define ITEM_H

#include "area.h"

#include <string> //std::string

using std::string;

/*! \brief Item hanler.
 *         Item expands area class with image and moving funtions.
 */
class Item: public Area
{
    private:
        std::string room_parent;
        std::string _image;
    public:
        Item(std::string name);
        virtual ~Item();
    public:
        void move(std::string room);
        std::string parent();
        void image(std::string id);
        std::string image();
};

#endif // ITEM_H
