#include "animation.h"

Animation::Animation(std::string object, int duration) :
    _object(object), _duration(duration), _easing(LINEAR)
{
}



Animation::Easing Animation::strToEasing(std::string s)
{
    if (s == "LINEAR")
        return LINEAR;
    else
        return UNDEFINED;
}

void Animation::setEasing(Animation::Easing easing)
{
    _easing = easing;
}

void Animation::addProperty(std::string name, float from, float to)
{
    AnimProperty p;
    p.property = name;
    p.from = from;
    p.to = to;
    addProperty(p);
}

void Animation::addProperty(AnimProperty p)
{
    properties.push_back(p);
}
