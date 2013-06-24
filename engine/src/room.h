/**
 * \file
 * <!--
 * Copyright 2010,2011 Daniele Maccioni
 * All rights reserved.
 * -->
 *
 * \version $Id: room.h $
 * \author Daniele Maccioni <gendoikari@develer.com>
 */


#ifndef ROOM_H
#define ROOM_H

#include <map> //std::map
#include <string> //string
#include <vector> //std::vector

class Area;
class Item;

using std::string;

/*! \brief Room handler.
 *
 * Rooms have areas and items references.
 */
class Room
{
    public:
        /// Room id. It must be unique.
        const string id;
    private:
        string _bg;
        string _bgm;
        std::map<string, Area *> areas;
        std::map<string, Item *> _items;
    public:
        /// Creates a room with the given id.
        Room(const string name);
        ~Room();
    public:
        /// Gets background image id.
        string bg() const;
        /// Gets room background music.
        string bgm() const;
        /// Sets background image id.
        void setBg(const string name);
        /// Sets room background music.
        void setBgm(const string name);
        /// Creates an area in the room, and returns it.
        Area *addArea(const string name);
        /// Adds an item reference to the room, and returns it.
        Item *addItem(const string name, Item *item_ptr);
        /// Removes item reference from the room. Items is not removed from game.
        void remItem(const string name);
        /// Returns the area with the given id.
        Area *area(const string name);
        /// Returns the item with the given id.
        Item *item(const string name);
        /// Returns all items in the room.
        std::vector <Item *> items() const;

        /// It it exists, returns the event under the point.
        string eventAt(const float x, const float y) const;
        /// It it exists, returns the item under the point.
        Item *itemAt(const float x, const float y);
        /// It it exists, returns the area under the point.
        Area *areaAt(const float x, const float y);
};

#endif // ROOM_H
