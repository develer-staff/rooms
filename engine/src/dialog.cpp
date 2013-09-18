#include "dialog.h"

Dialog::Dialog(const string name, const string start): id(name), begin_step(start)
{

}

Dialog::~Dialog()
{
    for (std::map<string, DialogStep>::iterator i = steps.begin();
         i != steps.end(); ++i)
    {
        logger.write("Garbage collector: " + id + "." + i->second.id, Log::NOTE);
        delete i->second.event;
    }
    steps.clear();
}

void Dialog::reset()
{
    current_step = &steps[begin_step];
}

DialogStep *Dialog::step(const string name)
{
    std::map<string, DialogStep>::iterator i = steps.find(name);
    if (i == steps.end())
        return 0;
    else
        return &(i->second);
}

std::vector <Action *> Dialog::actions()
{
    return current_step->event->actions();
}

std::vector <Action *> Dialog::jump(const string step_name)
{
    std::map <string, DialogStep>::iterator i = steps.find(step_name);
    if (i == steps.end())
        return std::vector<Action *>();
    current_step = &((*i).second);
    return actions();
}

string Dialog::text() const
{
    return current_step->text;
}

std::vector< std::pair<string, string> > Dialog::links()
{
    return current_step->links;
}

DialogStep *Dialog::addStep(const string name, const string text)
{
    DialogStep *step = &steps[name];
    step->id = name;
    step->text = text;
    step->event = new Event(id + name);
    return step;
}

void Dialog::addLink(const string name, const string dest, const string text)
{
    steps[name].links.push_back(std::make_pair(dest, text));
}
