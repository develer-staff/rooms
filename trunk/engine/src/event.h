#ifndef EVENT_H
#define EVENT_H

#include <string> //std::string
#include <vector> //std::vector
#include <utility> //std::pair std::make_pair

using std::string;

class Action;

/*! \brief Event Handler.
 *         It's a list of actions with requirements.
 */
class Event
{
    private:
        std::vector <Action *> _actions;
        std::vector <std::pair <string, string> > item_reqs;
        std::vector <std::pair <string, int> > var_reqs;
    public:
        Event(string name);
        virtual ~Event();
    public:
        const std::string id;
        Action *addAction(string name);
        std::vector <Action *> actions();
        void addItemReq(string name, string room);
        void addVarReq(string name, int value);
        std::vector <std::pair <string, string> > itemReqs();
        std::vector <std::pair <string, int> > varReqs();
};

#endif // EVENT_H
