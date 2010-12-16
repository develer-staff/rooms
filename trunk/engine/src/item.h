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
        Item(const std::string name);
        virtual ~Item();
    public:
        void move(const std::string room);
        std::string parent() const;
        void image(const std::string id);
        std::string image() const;
};

#endif // ITEM_H
