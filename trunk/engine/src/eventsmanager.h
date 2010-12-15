#ifndef EVENTSMANAGER_H
#define EVENTSMANAGER_H

#include <string> //std::string
#include <map> //std::map
#include <vector> //std::vector
#include <utility> //std::pair

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
        void var(string id, int value);
        int var(string id);
    private:
        bool checkItemReqs(std::vector <std::pair <string, string> > reqs);
        bool checkVarReqs(std::vector <std::pair <string, int> > reqs);
};

#endif // EVENTSMANAGER_H
