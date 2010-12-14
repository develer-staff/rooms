#ifndef EVENT_H
#define EVENT_H

#include <string> //std::string
#include <vector> //std::vector

class Action;

/*! \brief Event Handler.
 *         It's a list of actions with requirements.
 */
class Event
{
    private:
        std::vector <Action *> _actions;
    public:
        Event(std::string name);
        virtual ~Event();
    public:
        const std::string id;
        Action *addAction(std::string id);
        std::vector <Action *> actions();
};

#endif // EVENT_H
