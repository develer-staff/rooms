#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <vector>
#include <map>

using std::string;

struct AnimProperty {
    string property;
    float from;
    float to;
};

/**
 * \brief The Animation class
 *
 * Describes the animated properties of a single object
 */
class Animation
{
public:
    /**
     * \brief creates an Animation
     * \param object the animated object id
     * \param duration the animation duration in milliseconds
     */
    Animation(string object, int duration);

    enum Easing {
        UNDEFINED,
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
     * \brief strToEasing
     * \param s the string
     * \return the the Easing corresponding to the given string
     * Easing::UNDEFINED if the string does not match
     */
    static Animation::Easing strToEasing(string s);

    /// Animated object id
    string object() const;

    /// Animation duration in milliseconds
    virtual int duration() const;

    /**
     * \brief setEasing
     * \param easing the easing type to set
     */
    void setEasing(const Easing easing);

    /**
     * \brief addProperty add a property to animate
     * \param name it can be either x, y, width, height or alpha
     * \param from start value
     * \param to end value
     */
    void addProperty(const string name, const float from, const float to);

    /**
     * \brief addProperty
     * \param p the animated property
     */
    void addProperty(AnimProperty p);

    /**
     * \brief getStatus gets the animated properties status
     * \param millisecond_elapsed the milliseconds since the animation beginning
     * \return The property name and his value
     */
    virtual std::map<std::string, float> getStatus(int millisecond_elapsed);

private:
    float relativeProgress(int millisecond_elapsed);

private:
    string _object;
    int _duration;
    Easing _easing;
    std::vector<AnimProperty> properties;
};

#endif // ANIMATION_H
