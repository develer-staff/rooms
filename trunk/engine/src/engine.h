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
        RoomsManager *_rooms_mgr;
        EventsManager *_events_mgr;
        std::map<string, string> _images;
    public:
        virtual ~Engine();
    private:
        Engine();
    public:
        static Engine *createEngine();
        static void exit();
        void click (int x, int y);
        bool loadWorld(string filename);
        void loadGame(string filename);
        RoomsManager *getRoomsManager();
        EventsManager *getEventsManager();
        Engine::State state();
        void log(string text, int level);
        void exit(int status);
        std::vector<std::pair<string, string> > getImgNames();
    private:
        void execActions(std::vector <Action *> actions);
        void createImgsFromXml(std::vector <TiXmlElement *> images);
        void createEventsFromXml(std::vector <TiXmlElement *> events);
        void createRoomsFromXml(std::vector <TiXmlElement *> rooms);
        void createItemsFromXml(std::vector <TiXmlElement *> items);
        //RISC API
        void apiRoomGoto(string id);
        void apiVarSet(string id, int value);
        void apiItemMove(string id,string dest);
        void apiAreaSetEnable(string id, int value);
};

#endif // ROOMSENGINE_H
