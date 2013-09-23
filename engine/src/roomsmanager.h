/**
 * \file
 * <!--
 * Copyright 2010,2011 Daniele Maccioni
 * All rights reserved.
 * -->
 *
 * \version $Id: roomsmanager.h $
 * \author Daniele Maccioni <gendoikari@develer.com>
 */

#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#define ROOM_INV "!INVENTORY"
#define ROOM_NOWHERE "!NOWHERE"

#include <string> //string
#include <map> //std::map
#include <vector> //std::vector

class Room;
class Area;
class Item;

using std::string;


namespace utils
{
	template <class T> void freeElements(std::map<string, T *> &container);
	template <class T> T *getElement(string name, std::map<string, T *> container);
}

/** \brief The RoomsManager class handles rooms.
 *
 * Creates and destroys rooms.
 */
class RoomsManager
{
private:
    std::map <string, Room *> rooms;
    std::map <string, Item *> items;
    string _name;
    int _height;
    int _width;
    Room *current_room;
    Room *previous_room;
public:
    RoomsManager();
    ~RoomsManager();
public:
	/// Creates a Room with a given id and a given background.
	Room *addRoom(const string name, const string bg);
	/// Adds a created Room to the internal rooms list.
	void addRoom(Room *room);
	/// Creates an Area and initializes it with given values.
	Area *addArea(const string name, const string room, const float x, const float y,
				const float w, const float h, const string event);
	/// Creates an Item and initializes it with given values.
	Item *addItem(const string name, const string room, const float x, const float y,
				const float w, const float h, const string event, const string image);
	/// Adds a created Item to the internal item list.
	void addItem(Item *item);
	/// Returns a room with given id.
	Room *room(const string name);
	/// Returns an area with given id.
	Area *area(const string name);
	/// Returns an item with given id.
	Item *item(const string name);
	/// Returns items list
	std::map <string, Item *> getItems();
	/// Sets world/game name.
	void setWorldName(const string name);
	/// Gets the world/game name.
	string worldName() const;
	/// Sets the game rooms size.
	void setRoomSize(const int width, const int height);
	/// Gets rooms absolute height.
	int height() const;
	/// Gets rooms absolute width.
	int width() const;
	/// Sets where player is at the moment.
	void setCurrentRoom(const string name);
	/// Gets the current room.
	Room *currentRoom();
    /// Gets the previous room
    Room *previousRoom();
	/// Gets the event id under a point, if it exists. It returns "" otherwise.
	string eventAt(const float x, const float y);
	/// Moves the given item to the given room. It updates both source room and destination room.
	void moveItem(const string name, const string dest);
	/// Checks if a list of item requirements is satisfied.
	bool checkItemPlace(const std::vector <std::pair <string, string> > reqs);
};



#endif // ROOMMANAGER_H
