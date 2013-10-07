#include "delayedanimation.h"

DelayedAnimation::DelayedAnimation(std::string object, int duration, int delay) :
    Animation(object, duration),
    _delay(delay)
{
}

int DelayedAnimation::duration() const
{
    return Animation::duration() + _delay;
}

std::map<std::string, float> DelayedAnimation::getStatus(int millisecond_elapsed)
{
    std::map<std::string, float> res;
    int time = millisecond_elapsed - _delay;
    if (time < 0)
        return res;
    return Animation::getStatus(time);
}
