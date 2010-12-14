#ifndef ROOMSENGINE_H
#define ROOMSENGINE_H

#define DEBUG_LEVEL 3

#include <QtGui>
#include <string>
#include <fstream> //ofstream
#include <time.h> //time()

#include "xmlutils.h"
#include "../lib/tinyxml/tinyxml.h"

class RoomsManager;
class EventsManager;
class Event;
class Action;
class DrawDevice;
class Area;

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
        virtual ~Engine();
        bool initialize();
        void click (int x, int y);
        bool loadWorld(std::string filename);
        void loadGame(std::string filename);
        RoomsManager *getRoomsManager();
        EventsManager *getEventsManager();
        void setDevice(DrawDevice *device);
        Engine::State state();
        void log(std::string text, int level);
        void exit(int status);
    protected:
    private:
        Engine();
        static Engine *_engine;
        Engine::State _state;
        RoomsManager *_rooms_mgr;
        EventsManager *_events_mgr;
        DrawDevice *_device;
        bool createImgsFromXml(std::vector <TiXmlElement *> images);
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
