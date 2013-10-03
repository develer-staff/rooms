#ifndef ANIMATIONSMANAGER_H
#define ANIMATIONSMANAGER_H
#include "animation.h"
#include "sequentialanimation.h"
#include "timer.h"
#include "gui.h"

#include <map>
#include <string>

/**
 * \brief The AnimationsManager class handles animations
 *
 * The class uses a timer to get the right position of
 * objects during the animation
 */
class AnimationsManager
{
public:
    AnimationsManager();
    ~AnimationsManager();

    /// adds the animations to run
    void addParallelAnimations(std::vector<Animation *> anims);

    void addSequentialAnimation(SequentialAnimation * anim);

    /**
     * \brief hasAnimations
     * \return true if it contains some animations
     */
    bool hasAnimations();

    /**
     * \brief isAnimating
     * \return true if animations are running
     */
    bool isAnimating();

    /**
     * \brief stopIfOvertime
     * \return true if it is stopped because of overtime
     */
    bool stopIfOvertime();

    /// Starts animations
    void startAnimations();

    /**
     * \brief updateObjectState updates the specified object if it is animated
     * \param id identifier of the object to update
     * \param current datas that are being updated
     */
    void updateObjectState(const std::string id, GuiData *current);

private:
    void emptyCurrentAnimations();

    static float zeroIfNegative(float n);

private:
    Timer *timer;
    int max_time;
    std::vector<SequentialAnimation *> current_animations;

    // Unittests stuff
    friend class AnimationsTest;
};

#endif // ANIMATIONSMANAGER_H
