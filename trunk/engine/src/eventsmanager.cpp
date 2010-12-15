#include "eventsmanager.h"
#include "event.h"
#include "action.h"
#include "engine.h"

EventsManager::EventsManager(Engine *eng)
{
    engine = eng;
}

EventsManager::~EventsManager()
{
    for (std::map<string, Event *>::iterator i = events.begin();
         i != events.end(); ++i)
    {
        delete i->second;
    }
    events.clear();
}

Event *EventsManager::addEvent(string id)
{
    if (event(id) != 0)
        return 0;
    else
    {
        Event *e = new Event(id);
        events[id] = e;
        return e;
    }
}

Event *EventsManager::event(string id)
{
    std::map<string, Event *>::iterator i = events.find(id);
    if (i == events.end())
        return 0;
    else
        return i->second;
}

int EventsManager::var(string id)
{
    std::map<string, int>::iterator i = _vars.find(id);
    if (i == _vars.end())
        return 0;
    else
        return i->second;
}

void EventsManager::var(string id, int value)
{
    _vars[id] = value;
}

std::vector <Action *> EventsManager::actionsForEvent(string id)
{
    Event *event = events[id];
    if (checkItemReqs(event->itemReqs()) && checkVarReqs(event->varReqs()))
    {
        engine->log("Requirements satisfied", 3);
        return event->actions();
    }
    else
    {
        engine->log("Requirements not satisfied", 3);
        std::vector <Action *> empty;
        return empty;
    }
}

bool EventsManager::checkItemReqs(std::vector <std::pair <string, string> > reqs)
{
    for (std::vector <std::pair <string, string> >::iterator i = reqs.begin();
         i != reqs.end(); ++i)
    {
        if (engine->getRoomsManager()->item(i->first)->parent() != i->second)
            return false;
    }
    return true;
}

bool EventsManager::checkVarReqs(std::vector <std::pair <string, int> > reqs)
{
    for (std::vector <std::pair <string, int> >::iterator i = reqs.begin();
         i != reqs.end(); ++i)
    {
        if (var(i->first) != i->second)
            return false;
    }
    return true;
}
