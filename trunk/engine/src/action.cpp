#include "action.h"

Action::Action(std::string name): id(name)
{
    //ctor
}

Action::~Action()
{
    //dtor
    _params.clear();
}

void Action::pushParam(std::string value)
{
    //values will be read like a lifo stack
    _params.push_back(value);
}

std::string Action::popStrParam()
{
    if (!_params.empty())
    {
        std::string value = _params.back();
        _params.pop_back();
        return value;
    }
    return "";
}

int Action::popIntParam()
{
    if (!_params.empty())
    {
        std::string value = _params.back();
        std::istringstream str_to_i(value);
        int value_int;
        str_to_i >> value_int;
        _params.pop_back();
        return value_int;
    }
    return 0;
}
