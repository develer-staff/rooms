#ifndef ROOMSENGINE_H
#define ROOMSENGINE_H

#define DEBUG_LEVEL 3

#include <QtGui>
#include <string>
#include <fstream> //ofstream
#include <time.h> //time()
#include <utility> //pair

class RoomsManager;
class EventsManager;
class Event;
class Action;
class Area;
class Room;
class Item;

#include "roomsmanager.h"
#include "room.h"
#include "item.h"
#include "eventsmanager.h"
#include "event.h"
#include "action.h"
#include "area.h"
#include "xmlutils.h"

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
    public:
        static Engine *createEngine();
        static void exit();
        virtual ~Engine();
        void click (int x, int y);
        bool loadWorld(std::string filename);
        void loadGame(std::string filename);
        RoomsManager *getRoomsManager();
        EventsManager *getEventsManager();
        Engine::State state();
        void log(std::string text, int level);
        void exit(int status);
        std::vector<std::pair<std::string, std::string> > getImgNames();
    protected:
    private:
        Engine();
        static Engine *_engine;
        Engine::State _state;
        RoomsManager *_rooms_mgr;
        EventsManager *_events_mgr;
        std::map<std::string, std::string> _images;
        void createImgsFromXml(std::vector <TiXmlElement *> images);
        void createEventsFromXml(std::vector <TiXmlElement *> events);
        void createRoomsFromXml(std::vector <TiXmlElement *> rooms);
        void createItemsFromXml(std::vector <TiXmlElement *> items);

        void execActions(std::vector <Action *> actions);
        //RISC API
        void apiRoomGoto(std::string id);
        void apiVarSet(std::string id, int value);
        void apiItemMove(std::string id, std::string dest);
        void apiAreaSetEnable(std::string id, int value);

};

#endif // ROOMSENGINE_H
