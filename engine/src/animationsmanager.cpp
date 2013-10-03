#include "animationsmanager.h"

AnimationsManager::AnimationsManager() :
    max_time(0)
{
    timer = new Timer();
}

AnimationsManager::~AnimationsManager()
{
    emptyCurrentAnimations();
    delete timer;
}

void AnimationsManager::addParallelAnimations(std::vector<Animation *> anims)
{
    SequentialAnimation *anim = new SequentialAnimation();
    AnimationStep *s = new AnimationStep();
    std::vector<Animation *>::iterator i;
    for (i = anims.begin(); i != anims.end(); ++i){
        s->addAnimation(*i);
    }
    if (max_time < s->duration())
        max_time = s->duration();
    anim->addStep(s);
    current_animations.push_back(anim);
}

void AnimationsManager::addSequentialAnimation(SequentialAnimation * anim)
{
    if (max_time < anim->duration())
        max_time = anim->duration();
    current_animations.push_back(anim);
}

bool AnimationsManager::hasAnimations()
{
    return !current_animations.empty();
}

bool AnimationsManager::isAnimating()
{
    return timer->isRunning();
}

bool AnimationsManager::stopIfOvertime()
{
    int elapsed = timer->elapsed();
    if (elapsed < max_time)
        return false;
    timer->reset();
    emptyCurrentAnimations();
    max_time = 0;
    return true;
}

void AnimationsManager::startAnimations()
{
    if (!timer->isRunning())
        timer->start();
}


void AnimationsManager::updateObjectState(const std::string element, GuiData *current)
{
    std::vector<SequentialAnimation*>::iterator i;
    for (i = current_animations.begin(); i != current_animations.end(); ++i){
        std::map<std::string, float> p = (*i)->getStatus(timer->elapsed(), element);
        std::map<std::string, float>::iterator j;
        for (j = p.begin(); j != p.end(); ++j){
            if ((*j).first == "x") {
                current->rect.x = (*j).second;
                continue;
            }
            if ((*j).first == "y") {
                current->rect.y = (*j).second;
                continue;
            }
            if ((*j).first == "width") {
                current->rect.w = zeroIfNegative((*j).second);
                continue;
            }
            if ((*j).first == "height") {
                current->rect.h = zeroIfNegative((*j).second);
                continue;
            }
            if((*j).first == "alpha") {
                current->alpha = zeroIfNegative((*j).second);
                if (current->alpha > 1){
                    current->alpha = 1;
                }
                continue;
            }
        }
    }
}

void AnimationsManager::emptyCurrentAnimations()
{
    std::vector<SequentialAnimation *>::iterator i;
    for (i = current_animations.begin(); i != current_animations.end(); ++i){
        delete (*i);
    }
    current_animations.clear();
}

float AnimationsManager::zeroIfNegative(float n)
{
    if (n < 0)
        return 0;
    return n;
}
