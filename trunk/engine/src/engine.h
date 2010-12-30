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
#include "xmlutils.h"

#include <string> //std::string
#include <utility> //std::pair
#include <fstream> //std::ifstream


using std::string;

class Log;
class RoomsManager;
class EventsManager;
class Dialog;
class Event;
class Action;
class Area;
class Room;
class Item;

/*! \brief Main class.
 *         It's driven by frontend and it manages game state.
 */
class Engine
{
    public:
        static const string VERSION;
        enum State
        {
            INITIALIZING = 0,
            MENU,
            GAME,
            DIALOG,
            INVENTORY,
            ENDING
        };
        typedef std::vector<TiXmlElement *> XmlVect;
    private:
        Engine::State _state;
        RoomsManager *rooms_mgr;
        EventsManager *events_mgr;
        std::vector<string> images;
        std::map<string, Dialog *> dialogs;
        Dialog *dialog;
    public:
        Engine();
        ~Engine();
    public:
        void clickArea(const int x, const int y);
        void clickDialog(const string link);
        bool loadWorldFromStr(const string content);
        bool loadWorldFromFile(const string filename);
        void loadGame(const string filename);
        RoomsManager *getRoomsManager() const;
        EventsManager *getEventsManager() const;
        Engine::State state() const;
        void setState(const Engine::State state_name);
        std::vector<string> getImgNames() const;
        std::vector<Item *> getInventory() const;
        string getDialogText();
        std::map<string, string> getDialogChoices();
        Log *getLogger();
    private:
        void execActions(const std::vector <Action *> actions);
        void createImgsFromXml(XmlVect imgs);
        void fillEventFromXml(TiXmlElement *elem, Event *event);
        void createEventsFromXml(XmlVect events);
        void createRoomsFromXml(XmlVect rooms);
        void createItemsFromXml(XmlVect items);
        void createVarsFromXml(XmlVect vars);
        void createDialogsFromXml(XmlVect diags);
        //RISC API
        void apiRoomGoto(const string id);
        void apiVarSet(const string id, const int value);
        void apiItemMove(const string id, const string dest);
        void apiDialogStart(const string id);

        friend class MockEngine;
};

extern Log logger;

#endif // ROOMSENGINE_H
