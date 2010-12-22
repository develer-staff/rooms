#ifndef ROOMSENGINE_H
#define ROOMSENGINE_H

#include "log.h"
#include "roomsmanager.h"
#include "room.h"
#include "item.h"
#include "eventsmanager.h"
#include "event.h"
#include "action.h"
#include "area.h"
#include "xmlutils.h"

#include <string> //std::string
#include <utility> //std::pair

using std::string;

class Log;
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
        typedef std::vector<TiXmlElement *> XmlVect;
    private:
        static Engine *engine;
        Engine::State _state;
        RoomsManager *rooms_mgr;
        EventsManager *events_mgr;
        std::map<string, string> images;
    public:
        ~Engine();
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
        std::vector<std::pair<string, string> > getImgNames() const;
        Log *getLogger();
    private:
        void execActions(const std::vector <Action *> actions);
        void createImgsFromXml(XmlVect imgs);
        void createEventsFromXml(XmlVect events);
        void createRoomsFromXml(XmlVect rooms);
        void createItemsFromXml(XmlVect items);
        void createVarsFromXml(XmlVect vars);
        //RISC API
        void apiRoomGoto(const string id);
        void apiVarSet(const string id, const int value);
        void apiItemMove(const string id, const string dest);
};

extern Log logger;

#endif // ROOMSENGINE_H
