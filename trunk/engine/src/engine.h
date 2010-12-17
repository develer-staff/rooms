#ifndef ROOMSENGINE_H
#define ROOMSENGINE_H

#define DEBUG_LEVEL 3

#include "roomsmanager.h"
#include "room.h"
#include "item.h"
#include "eventsmanager.h"
#include "event.h"
#include "action.h"
#include "area.h"
#include "xmlutils.h"

#include <string> //std::string
#include <fstream> //std::ofstream
#include <time.h> //time()
#include <utility> //std::pair

using std::string;

class RoomsManager;
class EventsManager;
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
        static Engine *engine;
        Engine::State _state;
        RoomsManager *rooms_mgr;
        EventsManager *events_mgr;
        std::map<string, string> images;
    public:
        virtual ~Engine();
    private:
        Engine();
    public:
        static Engine *createEngine();
        static void exit();
        void click (const int x, const int y);
        bool loadWorld(const string filename);
        void loadGame(const string filename);
        RoomsManager *getRoomsManager() const;
        EventsManager *getEventsManager() const;
        Engine::State state() const;
        void state(const Engine::State state_name);
        void log(const string text, const int level);
        std::vector<std::pair<string, string> > getImgNames() const;
    private:
        void execActions(const std::vector <Action *> actions);
        void createImgsFromXml(std::vector <TiXmlElement *> imgs);
        void createEventsFromXml(std::vector <TiXmlElement *> events);
        void createRoomsFromXml(std::vector <TiXmlElement *> rooms);
        void createItemsFromXml(std::vector <TiXmlElement *> items);
        void createVarsFromXml(std::vector <TiXmlElement *> vars);
        //RISC API
        void apiRoomGoto(const string id);
        void apiVarSet(const string id, const int value);
        void apiItemMove(const string id, const string dest);
        void apiAreaSetEnable(const string id, const bool value);
};

#endif // ROOMSENGINE_H
