#ifndef EVENTSMANAGER_H
#define EVENTSMANAGER_H

#include <string> //std::string
#include <map> //std::map
#include <vector> //std::vector
#include <utility> //std::pair

class Event;
class Action;

using std::string;

/*! \brief Events interface.
 *         Creates and destroys events.
 */
class EventsManager
{
    private:
        std::map <string, Event *> events;
        //ATTENTION: var names that begin with '!' identify internal vars.
        std::map <string, int> _vars;
    public:
        EventsManager();
        ~EventsManager();
    public:
        Event *addEvent(const string name);
        void addEvent(Event *event);
        Event *event(const string name);
        std::vector <Action *> actionsForEvent(const string name);
        void setVar(const string name, const int value);
        int var(const string name) const;
        bool checkVarReqs(const std::vector <std::pair <string, int> > reqs) const;
};

#endif // EVENTSMANAGER_H
