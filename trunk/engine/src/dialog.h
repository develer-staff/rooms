#ifndef DIALOG_H
#define DIALOG_H

#include "engine.h"

#include <string> //std::string
#include <map> //std::map
#include <utility> //std::pair

using std::string;

class Engine;

struct DialogStep
{
    string id;
    Event *event;
    string text;
    string avatar;
    std::vector< std::pair<string, string> > links; //step id, choice text
};

class Dialog
{
    public:
        const string id;
    private:
        const string begin_step;
        DialogStep *current_step;
        std::map <string, DialogStep> steps;
    public:
        Dialog(const string name, const string start);
        ~Dialog();
    public:
        void reset();
        std::vector <Action *> jump(const string step_name);
        string text() const;
        DialogStep *addStep(const string name, const string text);
        void addLink(const string name, const string dest, const string text);
        DialogStep *step(const string name);
        std::vector <Action *> actions();
        std::vector< std::pair<string, string> > links();
};

#endif // DIALOG_H
