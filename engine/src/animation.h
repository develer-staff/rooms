#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <vector>

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

    void setEasing(Easing easing);
    void addProperty(string name, float from, float to);
    void addProperty(AnimProperty p);

private:
    string _object;
    int _duration;
    Easing _easing;
    std::vector<AnimProperty> properties;
};

#endif // ANIMATION_H
