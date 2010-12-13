#include "event.h"
#include "action.h"

Event::Event(std::string name): id(name)
{

}

Event::~Event()
{
    for (std::vector <Action *>::iterator i = _actions.begin(); i != _actions.end();
         i++)
    {
        delete (*i);
    }
    _actions.clear();
}

Action *Event::addAction(std::string id)
{
    _actions.push_back(new Action(id));
    return _actions.back();
}

std::vector <Action *> Event::actions()
{
    return _actions;
}
