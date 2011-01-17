#include "eventsmanager.h"
#include "event.h"
#include "action.h"

EventsManager::EventsManager()
{

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
    Event *e = new Event(name);
    addEvent(e);
    return e;
}

void EventsManager::addEvent(Event *event)
{
    events[event->id] = event;
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

std::map<string, int> EventsManager::getVars()
{
    return _vars;
}


void EventsManager::setVar(const string name, const int value)
{
    _vars[name] = value;
}

std::vector <Action *> EventsManager::actionsForEvent(const string name)
{
    return events[name]->actions();
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
