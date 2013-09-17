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

class Animation
{
public:
    Animation(string object, int duration);

    enum Easing {
        UNDEFINED,
        LINEAR
    };

    static Animation::Easing strToEasing(string s);

    string object() const;

    int duration() const;

    void setEasing(const Easing easing);
    void addProperty(const string name, const float from, const float to);
    void addProperty(AnimProperty p);
    std::map<std::string, float> getStatus(int millisecond_elapsed);

private:
    float relativeProgress(int millisecond_elapsed);

private:
    string _object;
    int _duration;
    Easing _easing;
    std::vector<AnimProperty> properties;
};

#endif // ANIMATION_H
