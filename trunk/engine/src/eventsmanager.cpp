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

Event *EventsManager::addEvent(const string name)
{
    if (event(name) != 0)
        return 0;
    else
    {
        Event *e = new Event(name);
        events[name] = e;
        return e;
    }
}

Event *EventsManager::event(const string name)
{
    std::map<string, Event *>::iterator i = events.find(name);
    if (i == events.end())
        return 0;
    else
        return i->second;
}

int EventsManager::var(const string name) const
{
    std::map<string, int>::const_iterator i = _vars.find(name);
    if (i == _vars.end())
        return 0;
    else
        return i->second;
}

void EventsManager::var(const string name, const int value)
{
    _vars[name] = value;
}

std::vector <Action *> EventsManager::actionsForEvent(const string name)
{
    Event *event = events[name];
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

bool EventsManager::checkItemReqs(const std::vector <std::pair <string, string> > reqs) const
{
    for (std::vector <std::pair <string, string> >::const_iterator i = reqs.begin();
         i != reqs.end(); ++i)
    {
        if (engine->getRoomsManager()->item(i->first)->parent() != i->second)
            return false;
    }
    return true;
}

bool EventsManager::checkVarReqs(const std::vector <std::pair <string, int> > reqs) const
{
    for (std::vector <std::pair <string, int> >::const_iterator i = reqs.begin();
         i != reqs.end(); ++i)
    {
        if (var(i->first) != i->second)
            return false;
    }
    return true;
}
