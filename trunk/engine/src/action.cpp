#include "action.h"

Action::Action(const std::string name): id(name)
{

}

Action::~Action()
{
    params.clear();
}

void Action::pushParam(const std::string value)
{
    //values will be read like a lifo stack
    params.push_back(value);
}

std::string Action::popStrParam()
{
    if (!params.empty())
    {
        std::string value = params.back();
        params.pop_back();
        return value;
    }
    return "";
}

int Action::popIntParam()
{
    if (!params.empty())
    {
        std::string value = params.back();
        std::istringstream str_to_i(value);
        int value_int;
        str_to_i >> value_int;
        params.pop_back();
        return value_int;
    }
    return 0;
}
