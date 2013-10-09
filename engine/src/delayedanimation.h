#ifndef DELAYEDANIMATION_H
#define DELAYEDANIMATION_H

#include "animation.h"

#include <string>

class DelayedAnimation : public Animation
{
public:
    DelayedAnimation(std::string object, int duration, int delay);

    int duration() const;

    std::map<std::string, float> getStatus(int millisecond_elapsed);

private:
    int _delay;
};

#endif // DELAYEDANIMATION_H
