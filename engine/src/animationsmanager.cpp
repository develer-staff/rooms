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

void AnimationsManager::addAnimations(std::vector<Animation *> anims)
{
    std::vector<Animation *>::iterator i;
    for (i = anims.begin(); i != anims.end(); ++i){
        if ((*i)->duration() > max_time)
            max_time = (*i)->duration();
        current_animations[(*i)->object()] = (*i);
    }
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
    std::map<std::string, Animation *>::iterator anims = current_animations.find(element);
    if (anims == current_animations.end())
        return;
    std::map<std::string, float> p = (*anims).second->getStatus(timer->elapsed());
    std::map<std::string, float>::iterator i;
    for (i = p.begin(); i != p.end(); ++i){
        if ((*i).first == "x") {
            current->rect.x = (*i).second;
            continue;
        }
        if ((*i).first == "y") {
            current->rect.y = (*i).second;
            continue;
        }
        if ((*i).first == "width") {
            current->rect.w = (*i).second;
            continue;
        }
        if ((*i).first == "height") {
            current->rect.h = (*i).second;
            continue;
        }
        if((*i).first == "alpha") {
            current->alpha = (*i).second*255;
            continue;
        }
    }
}

void AnimationsManager::emptyCurrentAnimations()
{
    current_animations.clear();
}
