/**
 * \file
 * <!--
 * Copyright 2010,2011 Daniele Maccioni
 * All rights reserved.
 * -->
 *
 * \version $Id: item.h $
 * \author Daniele Maccioni <gendoikari@develer.com>
 */


#ifndef ITEM_H
#define ITEM_H

#include "area.h"

#include <string> //std::string

using std::string;

/** \brief Item handler.
 *
 * Item expands area class with image and moving funtions.
 */
class Item: public Area
{
    private:
        std::string room_parent;
        std::string _image;
    public:
        /// Creates an item with the given id.
        Item(const std::string name);
        ~Item();
    public:
        /// Moves the item in the given room. It doesn't update the room.
        void move(const std::string room);
        /// Gets item location.
        std::string parent() const;
        /// Sets item image.
        void setImage(const std::string name);
        /// Gets item image.
        std::string image() const;
};

#endif // ITEM_H
