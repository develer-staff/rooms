#include "event.h"
#include "action.h"

Event::Event(const string name): id(name)
{

}

Event::~Event()
{
    for (std::vector <Action *>::iterator i = _actions.begin(); i != _actions.end();
         ++i)
    {
        std::vector<Animation *> a = (*i)->animations();
        for (std::vector<Animation *>::iterator j = a.begin(); j != a.end(); ++j){
            delete (*j);
        }
        a.clear();
        delete (*i);
    }
    _actions.clear();
}

Action *Event::addAction(const string name)
{
    _actions.push_back(new Action(name));
    return _actions.back();
}

std::vector <Action *> Event::actions() const
{
    return _actions;
}

void Event::addItemReq(const string name, const string room)
{
    item_reqs.push_back(std::make_pair(name, room));
}

std::vector <std::pair <string, string> > Event::itemReqs() const
{
    return item_reqs;
}

void Event::addVarReq(const string name, const int value)
{
    var_reqs.push_back(std::make_pair(name, value));
}

std::vector <std::pair <string, int> > Event::varReqs() const
{
    return var_reqs;
}
