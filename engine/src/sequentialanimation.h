#ifndef SEQUENTIALANIMATION_H
#define SEQUENTIALANIMATION_H
#include "animation.h"

#include <vector>
#include <string>

class AnimationStep
{
public:
    AnimationStep();

    void addAnimation(Animation *a);
    int duration() const;
    std::vector<Animation *> animations() const;
    Animation *getAnimation(std::string id);

private:
    std::vector<Animation *> _animations;
    int _duration;
};

class SequentialAnimation
{
public:
    SequentialAnimation();
    ~SequentialAnimation();

    void addStep(AnimationStep *s);

    int duration();

    std::map<std::string, float> getStatus(int elapsed, const std::string id);

private:
    std::vector<AnimationStep *> queue;
    int total_time;


};

#endif // SEQUENTIALANIMATION_H
