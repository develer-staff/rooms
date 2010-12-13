#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <vector>

class Action;

class Event
{
    public:
        Event(std::string name);
        virtual ~Event();
        const std::string id;
        Action *addAction(std::string id);
        std::vector <Action *> actions();
    protected:
    private:
        std::vector <Action *> _actions;
};

#endif // EVENT_H
