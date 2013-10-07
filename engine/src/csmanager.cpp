#include "csmanager.h"
#include "delayedanimation.h"

CsManager::CsManager()
{
}

CsManager::~CsManager()
{
    endCutscene();
}

bool CsManager::startCutscene(const std::string &csPath, const std::vector<std::string> &images)
{
    CsParser p(images);
    if (!p.parse(csPath)){
        logger.write("Parser error: "+p.getErrorMessage(), Log::ERROR);
        return false;
    }
    animated_objects = p.objects();
    steps = p.steps();
    initial_steps = p.startingSteps();
    setInitialVisibleData();

    logger.write("Cutscene loaded succesfully", Log::NOTE);
    return true;
}

std::vector<Animation *> CsManager::getAnimations(){
    std::vector<Animation *> result;
    std::vector<std::string>::iterator i;
    for (i = initial_steps.begin(); i != initial_steps.end(); ++i){
        addDelayedAnimations(0, (*i), &result);
    }
    return result;
}

void CsManager::endCutscene()
{
    animated_objects.clear();
    steps.clear();
    initial_steps.clear();
    std::vector<Animation *>::iterator i;
    for (i = animations_garbage.begin(); i != animations_garbage.end(); ++i){
        delete (*i);
    }
    animations_garbage.clear();
}

GuiDataVect CsManager::getVisibleData()
{
    return visible_data;
}

void CsManager::setVisibleData(GuiDataVect v)
{
    visible_data = v;
}

void CsManager::addDelayedAnimations(int delay, std::string stepName, std::vector<Animation *> *animations)
{
    CsStep step = steps[stepName];
    if (step.objStates.size() == 0){
        Animation *a = new DelayedAnimation("!null", step.duration, delay);
        animations->push_back(a);
        animations_garbage.push_back(a);
    }

    std::map<std::string, CsState>::iterator i;
    for (i = step.objStates.begin(); i != step.objStates.end(); ++i){
        Animation *a = new DelayedAnimation((*i).first, step.duration, delay);
        CsState::iterator j;
        for (j = (*i).second.begin(); j != (*i).second.end(); ++j){
            a->addProperty((*j).first, animatedObject((*i).first)->state[(*j).first], (*j).second);
            animatedObject((*i).first)->state[(*j).first] = (*j).second;
        }
        animations->push_back(a);
        animations_garbage.push_back(a);
    }

    std::vector<std::string>::iterator k;
    for (k = step.next.begin(); k != step.next.end(); ++k){
        addDelayedAnimations(delay+step.duration, (*k), animations);
    }
}

void CsManager::setInitialVisibleData()
{
    std::vector<CsObject>::iterator i;
    for (i = animated_objects.begin(); i != animated_objects.end(); ++i){
        CsObject o = (*i);
        GuiData gd;
        gd.alpha = 0;
        gd.id = o.name;
        gd.rect = GuiRect(0, 0, 0, 0);
        gd.image = "";
        gd.text = "";
        if (o.isText)
            gd.text = o.content;
        else
            gd.image = o.content;
        CsState::iterator j;
        for (j = o.state.begin(); j != o.state.end(); ++j){
            if ((*j).first == "x")
                gd.rect.x = (*j).second;
            if ((*j).first == "y")
                gd.rect.y = (*j).second;
            if ((*j).first == "width")
                gd.rect.w = (*j).second;
            if ((*j).first == "height")
                gd.rect.h = (*j).second;
            if ((*j).first == "alpha")
                gd.alpha = (*j).second;
        }
        visible_data.push_back(gd);
    }
}

CsObject *CsManager::animatedObject(const std::string &name)
{
    std::vector<CsObject>::iterator i;
    for (i = animated_objects.begin(); i != animated_objects.end(); ++i){
        if ((*i).name == name)
            return &(*i);
    }
    return 0;
}
