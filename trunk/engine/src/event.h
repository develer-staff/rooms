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
    public:
        const std::string id;
    private:
        std::vector <Action *> _actions;
        std::vector <std::pair <string, string> > item_reqs;
        std::vector <std::pair <string, int> > var_reqs;
    public:
        Event(const string name);
        virtual ~Event();
    public:
        Action *addAction(const string name);
        std::vector <Action *> actions() const;
        void addItemReq(const string name, const string room);
        void addVarReq(const string name, const int value);
        std::vector <std::pair <string, string> > itemReqs() const;
        std::vector <std::pair <string, int> > varReqs() const;
};

#endif // EVENT_H
