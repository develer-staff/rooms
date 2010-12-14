#ifndef EVENTSMANAGER_H
#define EVENTSMANAGER_H

#include <string> //std::string
#include <map> //std::map
#include <vector> //std::vector

class Engine;
class Event;
class Action;

using std::string;

/*! \brief Events interface.
 *         Creates and destroys events.
 */
class EventsManager
{
    private:
        Engine *engine;
        std::map <string, Event *> events;
        //ATTENTION: var names that begin with '!' identify internal vars.
        std::map <string, int> _vars;
    public:
        EventsManager(Engine *eng);
        virtual ~EventsManager();
    public:
        Event *addEvent(string id);
        Event *event(string id);
        std::vector <Action *> actionsForEvent(string id);
        int var(string id);
        void var(string id, int value);
};

#endif // EVENTSMANAGER_H
