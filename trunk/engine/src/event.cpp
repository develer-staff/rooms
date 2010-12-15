#include "event.h"
#include "action.h"

Event::Event(string name): id(name)
{

}

Event::~Event()
{
    for (std::vector <Action *>::iterator i = _actions.begin(); i != _actions.end();
         ++i)
    {
        delete (*i);
    }
    _actions.clear();
}

Action *Event::addAction(string name)
{
    _actions.push_back(new Action(name));
    return _actions.back();
}

std::vector <Action *> Event::actions()
{
    return _actions;
}

void Event::addItemReq(string name, string room)
{
    item_reqs.push_back(std::make_pair(name, room));
}

std::vector <std::pair <string, string> > Event::itemReqs()
{
    return item_reqs;
}

void Event::addVarReq(string name, int value)
{
    var_reqs.push_back(std::make_pair(name, value));
}

std::vector <std::pair <string, int> > Event::varReqs()
{
    return var_reqs;
}
