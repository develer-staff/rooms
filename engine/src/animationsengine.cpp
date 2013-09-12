#include "animationsengine.h"

AnimationsEngine::AnimationsEngine()
{
    _timer = new Timer();
}

AnimationsEngine::~AnimationsEngine()
{
    delete _timer;
}

void AnimationsEngine::addAnimation(Animation *animation)
{
    _animations.push_back(animation);
}

void AnimationsEngine::startAnimations()
{
    if (_timer->isRunning())
        return;
    _timer->start();
}

AnimationStatusVect AnimationsEngine::getAnimationsStatus()
{
    AnimationStatusVect result;
    std::vector<Animation *>::iterator i;
    int elapsed = _timer->elapsed();
    for (i = _animations.begin(); i != _animations.end(); ++i){
        result.push_back((*i)->status(elapsed));
    }
    return result;
}

bool AnimationsEngine::isRunning()
{
    return _timer->isRunning();
}

void AnimationsEngine::stopAndClear()
{
    _animations.clear();
    _timer->reset();
}
