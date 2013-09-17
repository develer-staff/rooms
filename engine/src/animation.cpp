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

std::string Animation::object() const
{
    return _object;
}

int Animation::duration() const
{
    return _duration;
}

void Animation::setEasing(const Easing easing)
{
    _easing = easing;
}

void Animation::addProperty(const std::string name, const float from, const float to)
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

std::map<std::string, float> Animation::getStatus(int millisecond_elapsed)
{
    float progress = relativeProgress(millisecond_elapsed);
    std::map<std::string, float> res;
    std::vector<AnimProperty>::iterator i;
    for (i = properties.begin(); i != properties.end(); ++i){
        res[(*i).property] = (*i).from + (float((*i).to - (*i).from) * progress);
    }
    return res;
}

float Animation::relativeProgress(int millisecond_elapsed)
{
    float progress = float(millisecond_elapsed)/float(_duration);
    if (progress > 1.0)
        progress = 1.0;
    switch (_easing){
    case UNDEFINED:
        return 1.0;
    case LINEAR:
        return progress;
    }
    return 1.0;
}
