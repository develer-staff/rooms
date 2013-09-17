#ifndef ANIMATIONSMANAGER_H
#define ANIMATIONSMANAGER_H
#include "animation.h"
#include "timer.h"
#include "gui.h"

#include <map>
#include <string>

class AnimationsManager
{
public:
    AnimationsManager();
    ~AnimationsManager();

    void addAnimations(std::vector<Animation *> anims);

    /**
     * \brief hasAnimations
     * \return true if it contains some animations
     */
    bool hasAnimations();

    /**
     * \brief isAnimating
     * \return true if the animations are running
     */
    bool isAnimating();

    /**
     * \brief stopIfOvertime
     * \return true if it is stopped because of overtime
     */
    bool stopIfOvertime();

    void startAnimations();

    void updateObjectState(const std::string id, GuiData *current);

private:
    void emptyCurrentAnimations();

private:
    Timer *timer;
    int max_time;
    std::map<std::string, Animation *> current_animations;
};

#endif // ANIMATIONSMANAGER_H
