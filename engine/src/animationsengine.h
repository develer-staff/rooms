#ifndef ANIMATIONSENGINE_H
#define ANIMATIONSENGINE_H
#include <vector>

#include "timer.h"
#include "animation.h"

//TODO: completare documentazione

/**
 * \brief The AnimationsEngine class can run Animations
 *
 */
class AnimationsEngine
{
public:
    AnimationsEngine();
    ~AnimationsEngine();

    /**
     * \brief addAnimation
     * \param animation the animation to be added
     */
    void addAnimation(Animation *animation);
    void startAnimations();
    AnimationStatusVect getAnimationsStatus();
    bool isRunning();
    void stopAndClear();

private:
    Timer *_timer;
    std::vector<Animation *> _animations;
};

#endif // ANIMATIONSENGINE_H
