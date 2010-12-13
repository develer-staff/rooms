#ifndef ROOMSENGINE_H
#define ROOMSENGINE_H

#include <QtGui>
#include <string> //std::string

#include "../lib/tinyxml/tinyxml.h"

class RoomsManager;
class EventsManager;
class Event;
class Action;
class DrawDevice;

class RoomsEngine
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
        static RoomsEngine *createEngine();
        virtual ~RoomsEngine();
        int initialize();
        void click (int x, int y);
        bool loadWorld(std::string filename);
        void loadGame(std::string filename);
        RoomsManager *getRoomsManager();
        EventsManager *getEventsManager();
        void setDevice(DrawDevice *device);
        RoomsEngine::State state();
    protected:
    private:
        RoomsEngine();
        static RoomsEngine *_engine;
        RoomsEngine::State _state;

        RoomsManager *_rooms_mgr;
        EventsManager *_events_mgr;
        DrawDevice *_device;

        void execActions(std::vector <Action *> actions);
        //RISC API
        void ROOM_GOTO(std::string id);

};

#endif // ROOMSENGINE_H
