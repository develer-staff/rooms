#ifndef SEQUENTIALANIMATION_H
#define SEQUENTIALANIMATION_H
#include "animation.h"

#include <vector>
#include <string>

/**
 * \brief The AnimationStep class rapresent a step of a SequentialAnimation
 *
 * Each step can run one or more animations at the same time
 */
class AnimationStep
{
public:
    AnimationStep();

    ///Adds an animation to this step
    void addAnimation(Animation *a);

    /// Returns the duration in milliseconds
    int duration() const;

    /// Returns animaions in this step
    std::vector<Animation *> animations() const;

    /// Returns the animation with the given id if present, otherwise 0
    Animation *getAnimation(std::string id);

private:
    std::vector<Animation *> _animations;
    int _duration;
};

/**
 * \brief The SequentialAnimation class manages a sequence of animations
 */
class SequentialAnimation
{
public:
    SequentialAnimation();
    ~SequentialAnimation();

    /// Adds the step s at the end of the animation queue
    void addStep(AnimationStep *s);

    /// Returns the duration of the entire queue
    int duration();

    /**
     * \brief getStatus gets the properties of the object based on the animation time
     * \param elapsed the time elapsed in ms
     * \param id the id of the animated object
     * \return a map of properties if the object is animated, otherwise an empty map
     */
    std::map<std::string, float> getStatus(int elapsed, const std::string id);

private:
    std::vector<AnimationStep *> queue;
    int total_time;


};

#endif // SEQUENTIALANIMATION_H
