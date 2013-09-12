#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <map>

#include "gui.h"
#include "engine.h"

using std::string;

struct AnimatedProperty {
    string name;
    float from;
    float to;
};

/**
 * \brief The AnimationStatus struct is used to describe the current state of the animated object
 */
struct AnimationStatus {
    string object_id;
    std::map<string, float> properties;
};

typedef std::vector<AnimationStatus> AnimationStatusVect;

/**
 * \brief The AnimationDescriptor struct is used to encapsulate all the raw animation information
 */
struct AnimationDescriptor {
    string object_id;
    int duration;
    Animation::Easing easing;
    std::vector<AnimatedProperty> properties;
};

/**
 * \brief The Animation class
 *
 * Provides information about animation structure and the mehods to implement to create an animation
 */
class Animation
{
public:
    Animation(AnimationDescriptor desc);

    enum Easing {
        LINEAR,
        IN_QUAD,
        OUT_QUAD,
        IN_OUT_QUAD,
        IN_BACK,
        OUT_BACK,
        IN_OUT_BACK,
        IN_ELASTIC,
        OUT_ELASTIC,
        IN_OUT_ELASTIC
    };

    /**
     * \brief animation status
     *
     * \param millisecond_elapsed the time since the start of the animation
     * \return the updated GuiData
     */
    virtual AnimationStatus status(int millisecond_elapsed) = 0;

protected:
    string object_id;
    std::vector<AnimatedProperty> properties;
    int duration;
    Easing easing;

};

/**
 * \brief The InternalAnimation class
 *
 * Updates the properties of a GuiData structure based on the Easing type and the time elapsed
 */
class InternalAnimation : public Animation {
public:
    InternalAnimation(AnimationDescriptor desc);

    AnimationStatus status(int millisecond_elapsed);

private:
    float relativeProgress(int millisecond_elapsed);
    float getNewPosition(float start, float end, float progress);

};

#endif // ANIMATION_H
