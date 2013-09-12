#include <cmath>

#include "animation.h"

#define PI 3.1415926535

Animation::Animation(AnimationDescriptor desc) :
    object_id(desc.object_id), properties(desc.properties), duration(desc.duration), easing(desc.easing)
{
}

InternalAnimation::InternalAnimation(AnimationDescriptor desc)
    : Animation(desc)
{
}

AnimationStatus InternalAnimation::status(int millisecond_elapsed)
{
    //calculating animation progress
    float progress = relativeProgress(millisecond_elapsed);
    std::vector<AnimatedProperty>::iterator i;
    AnimationStatus status;
    status.object_id = object_id;
    for (i = properties.begin(); i != properties.end(); ++i){
        status.properties[i->name] = getNewPosition(i->from, i->to, progress);
    }
    return status;
}

float InternalAnimation::relativeProgress(int millisecond_elapsed)
{
    float progress = float(millisecond_elapsed)/float(_duration);
    if (progress > 1.0)
        progress = 1.0;

    switch(_type) {
    case LINEAR:
        return progress;

    case IN_QUAD:
        return progress * progress;

    case OUT_QUAD:
        return -1.0 * progress * (progress - 2.0);

    case IN_OUT_QUAD:
        float p = progress * 2;
        if (p < 1)
            return 0.5 * p * p;
        p -= 1.0;
        return -0.5 * (p * (p - 2.0) - 1.0);

    case IN_BACK:
        return progress * progress * ((1.70158 + 1.0) * progress - 1.70158);

    case OUT_BACK:
        float p = progress - 1.0;
        return p * p * ((1.70158 + 1) * p + 1.70158) + 1.0;

    case IN_OUT_BACK:
        float p = progress * 2.0;
        float s = 1.70158 * 1.525;
        if (p < 1)
            return 0.5 * (p * p * ((s + 1.0) * p - s));
        p -= 2.0;
        return 0.5 * (p * p * ((s + 1.0) * p + s) + 2.0);

    case IN_ELASTIC:
        float p = 0.3;
        float s = p / 4.0;
        float q = progress;
        if (q == 1)
            return 1.0;
        q -= 1.0;
        return -(pow(2, 10 * q) * sin((q - s) * (2 * PI) / p));

    case OUT_ELASTIC:
        p = 0.3;
        s = p / 4.0;
        q = progress;
        if (q == 1)
            return 1.0;
        return pow(2, -10 * q) * sin((q - s) * (2 * PI) / p) + 1.0;

    case IN_OUT_ELASTIC:
        float p = 0.3 * 1.5;
        float s = p / 4.0;
        float q = progress * 2;
        if (q == 2)
            return 1.0;
        q -= 1.0;
        if (q < 1)
            return -0.5 * (pow(2, 10 * q) * sin((q - s) * (2.0 *PI) / p));
        return pow(2, -10 * q) * sin((q - s) * (2.0 * PI) / p) * 0.5 + 1.0;
    }
}

float InternalAnimation::getNewPosition(float start, float end, float progress)
{
    if (start == end)
        return start;
    return start + ((end - start) * progress);
}
