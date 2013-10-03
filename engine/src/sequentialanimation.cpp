#include "sequentialanimation.h"

AnimationStep::AnimationStep() :
    _duration(0)
{
}

void AnimationStep::addAnimation(Animation *a)
{
    _animations.push_back(a);
    if (a->duration() > _duration)
        _duration = a->duration();
}

int AnimationStep::duration() const
{
    return _duration;
}

std::vector<Animation *> AnimationStep::animations() const
{
    return _animations;
}

Animation *AnimationStep::getAnimation(std::string id)
{
    std::vector<Animation *>::iterator i;
    for (i = _animations.begin(); i != _animations.end(); ++i){
        if ((*i)->object() == id){
            return (*i);
        }
    }
    return 0;
}

SequentialAnimation::SequentialAnimation() :
    total_time(0)
{
}

SequentialAnimation::~SequentialAnimation()
{
    std::vector<AnimationStep *>::iterator i;
    for (i = queue.begin(); i != queue.end(); ++i){
        delete (*i);
    }
    queue.empty();
}

void SequentialAnimation::addStep(AnimationStep *s)
{
    if (s->duration() == 0)
        return;
    queue.push_back(s);
    total_time += s->duration();
}

int SequentialAnimation::duration()
{
    return total_time;
}

std::map<std::string, float> SequentialAnimation::getStatus(int elapsed, const std::string id)
{
    std::vector<AnimationStep *>::iterator i = queue.begin();
    while (i != queue.end() && elapsed > (*i)->duration()){
        elapsed -= (*i)->duration();
        i++;
    }
    if(i == queue.end())
        return std::map<std::string, float>();
    Animation *a = (*i)->getAnimation(id);
    if (a == 0)
        return std::map<std::string, float>();
    return a->getStatus(elapsed);
}

