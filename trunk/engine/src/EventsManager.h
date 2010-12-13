#ifndef EVENTSMANAGER_H
#define EVENTSMANAGER_H

#include <string>
#include <map>
#include <vector>

class RoomsEngine;
class Event;
class Action;

class EventsManager
{
    public:
        EventsManager(RoomsEngine *engine);
        virtual ~EventsManager();
        Event *addEvent(std::string id);
        Event *event(std::string id);
        std::vector <Action *> actionsForEvent(std::string id);
    protected:
    private:
        RoomsEngine *_engine;

        std::map <std::string, Event *> _events;

};

#endif // EVENTSMANAGER_H
