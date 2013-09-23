#include "animation.h"

#include <math.h>

Animation::Animation(std::string object, int duration) :
    _object(object), _duration(duration), _easing(LINEAR)
{
}



Animation::Easing Animation::strToEasing(std::string s)
{
    if (s == "LINEAR")
        return LINEAR;
    if (s == "IN_QUAD")
        return IN_QUAD;
    if (s == "OUT_QUAD")
        return OUT_QUAD;
    if (s == "IN_OUT_QUAD")
        return IN_OUT_QUAD;
    if (s == "IN_BACK")
        return IN_BACK;
    if (s == "OUT_BACK")
        return OUT_BACK;
    if (s == "IN_OUT_BACK")
        return IN_OUT_BACK;
    if (s == "IN_ELASTIC")
        return IN_ELASTIC;
    if (s == "OUT_ELASTIC")
        return OUT_ELASTIC;
    if (s == "IN_OUT_ELASTIC")
        return IN_OUT_ELASTIC;
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
    {
        return 1.0;
    }
    case LINEAR:
    {
        return progress;
    }
    case IN_QUAD:
    {
        return progress * progress;
    }
    case OUT_QUAD:
    {
        return -1.0 * progress * (progress - 2.0);
    }
    case IN_OUT_QUAD:
    {
        float p = progress * 2;
        if (p < 1)
            return 0.5 * p * p;
        p -= 1.0;
        return -0.5 * (p * (p - 2.0) - 1.0);
    }
    case IN_BACK:
    {
        return progress * progress * ((1.70158 + 1.0) * progress - 1.70158);
    }
    case OUT_BACK:
    {
        float p = progress - 1.0;
        return p * p * ((1.70158 + 1) * p + 1.70158) + 1.0;
    }
    case IN_OUT_BACK:
    {
        float p = progress * 2.0;
        float s = 1.70158 * 1.525;
        if (p < 1)
            return 0.5 * (p * p * ((s + 1.0) * p - s));
        p -= 2.0;
        return 0.5 * (p * p * ((s + 1.0) * p + s) + 2.0);
    }
    case IN_ELASTIC:
    {
        float p = 0.3;
        float s = p / 4.0;
        float q = progress;
        if (q == 1)
            return 1.0;
        q -= 1.0;
        return -(pow(2, 10 * q) * sin((q - s) * (2 * M_PI) / p));
    }
    case OUT_ELASTIC:
    {
        float p = 0.3;
        float s = p / 4.0;
        float q = progress;
        if (q == 1)
            return 1.0;
        return pow(2, -10 * q) * sin((q - s) * (2 * M_PI) / p) + 1.0;
    }
    case IN_OUT_ELASTIC:
    {
        float p = 0.3 * 1.5;
        float s = p / 4.0;
        float q = progress * 2;
        if (q == 2)
            return 1.0;
        float qq = q - 1.0;
        if (q < 1)
            return -0.5 * (pow(2, 10 * qq) * sin((qq - s) * (2.0 * M_PI) / p));
        return pow(2, -10 * qq) * sin((qq - s) * (2.0 * M_PI) / p) * 0.5 + 1.0;
    }
    }
    return 1.0;
}
