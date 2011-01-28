/**
 * \file
 * <!--
 * Copyright 2010,2011 Daniele Maccioni
 * All rights reserved.
 * -->
 *
 * \version $Id: engine.h $
 * \author Daniele Maccioni <gendoikari@develer.com>
 *
 * \mainpage Rooms Engine
 *
 * Rooms Engine is a point-and-click andventure engine.
 * Usage simple example:
 * \code
 * Engine *eng = new Engine;
 * eng->loadWorldFromFile(my_valid_world_file);
 * //frontend event loop
 * switch(eng->state())
 *   case Engine::GAME:
 *     std::pair<float, float> coord = eng->absToRelCoord(mouse->x(), mouse->y());
 *     eng->clickArea(coord.first, coord.second);
 *     break;
 * \endcode
 */


#ifndef ROOMSENGINE_H
#define ROOMSENGINE_H

#include "log.h"
#include "roomsmanager.h"
#include "room.h"
#include "item.h"
#include "eventsmanager.h"
#include "dialog.h"
#include "event.h"
#include "action.h"
#include "area.h"
#include "roomsreader.h"
#include "gui.h"

#include <string> //std::string
#include <utility> //std::pair
#include <fstream> //std::ifstream


using std::string;

/*! \brief Engine Main class.
 *
 * Provides information about game structure and manages game objects through object managers like the RoomsManager.
 */
class Engine
{
public:

	enum State
	{
		INITIALIZING = 0,
		MENU,
		GAME,
		DIALOG,
		INVENTORY,
		ENDING
	};
private:
	Engine::State _state;
	RoomsManager *rooms_mgr;
	EventsManager *events_mgr;
	GuiManager *gui_mgr;
	std::vector<string> images;
	std::vector<string> sfx;
	std::map<string, Dialog *> dialogs;
	Dialog *dialog;
	GuiScrolledBar *inventory;
	GuiScrolledBar *dialog_list;
public:
	Engine();
	~Engine();
public:
	/**
	 * \brief Comunicates to engine that a click event happened and let engine completely manage it.
	 *
	 * Engine takes total control of the event, processing gui, dialogs, items and areas.
	 * \param x     X in relative coordinates.
	 * \param y     Y in relative coordinates.
	 */
	void click(const float x, const float y);
	/**
	 * \brief Comunicates to engine that an area could be activated.
	 *
	 * If there is an area under the click, engine checks the event and executes actions.
	 * \param x     X in relative coordinates.
	 * \param y     Y in relative coordinates.
	 */
	void clickArea(const float x, const float y);
	/**
	 * \brief Comunicates to engine that a dialogue choice has been clicked.
	 *
	 * Engine updates the dialogue and world data.
	 * \param link     It's the message chosen.
	 */
	void clickDialog(const string link);
	/**
	 * \brief Load world data from string.
	 *
	 * \param content     World data string.
	 * \return True if succeded in loading and parsing, false otherwise.
	 */
	bool loadWorldFromStr(const string content);
	/**
	 * \brief Load world data from file.
	 *
	 * \param filename     Path to a world data file.
	 * \return True if succeded in loading and parsing, false otherwise.
	 */
	bool loadWorldFromFile(const string filename);
	/// Saves game state in the given file
	void saveGame(const string filename);
	/// Loads the game state from the given file
	void loadGame(const string filename);
	/// Gets RoomsManager.
	RoomsManager *getRoomsManager() const;
	/// Gets EventsManager.
	EventsManager *getEventsManager() const;
	/// Gets GuiManager.
	GuiManager *getGuiManager() const;
	/// Gets the game state.
	Engine::State state() const;
	/// Sets the game state.
	void setState(const Engine::State state_name);
	/// Gets all the paths of images used in the game.
	std::vector<string> getImgNames() const;
	/// Gets all items in inventory.
	std::vector<Item *> getInventory() const;
	/// Gets the text of the current dialog.
	string getDialogText();
	/// Gets all dialog choices that satisfy requirements.
	std::map<string, string> getDialogChoices();
	/// Gets all sounds effects names that have to be played now. Clears sfx list after being called.
	std::vector<string> getSFX();
	/// Gets the logger.
	Log *getLogger();
	/**
	 * \brief Converts from absolute coordinates to game relative coordinates.
	 *
	 * All areas and items in the game use relative coordinates (0.0 - 1.0).
	 * \param x     X in pixel
	 * \param y     Y in pixel
	 * \return A pair of normalized coordinates.
	 */
	std::pair<float, float> absToRelCoord(const int x, const int y);
	/**
	 * \brief Converts from relative coordinates to absolute coordinates.
	 *
	 * All areas and items in the game use relative coordinates (0.0 - 1.0).
	 * \param x     Normalized X
	 * \param y     Normalized Y
	 * \return A pair of absolute coordinates.
	 */
	std::pair<int, int> relToAbsCoord(const float x, const float y);
	/**
	 * \brief Converts from relative coordinates rect to absolute coordinates rect.
	 *
	 * All areas and items in the game use relative coordinates (0.0 - 1.0).
	 */
	void relToAbsRect(GuiRect &rect);
private:
	void execActions(const std::vector <Action *> actions);
	void updateDialog();
	//RISC API
	void apiRoomGoto(const string id);
	void apiVarSet(const string id, const int value);
	void apiItemMove(const string id, const string dest);
	void apiDialogStart(const string id);
	void apiSFXPlay(const string id);
	friend class MockEngine;
};

extern Log logger;

#endif // ROOMSENGINE_H
