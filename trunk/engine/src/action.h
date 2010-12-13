#ifndef ACTION_H
#define ACTION_H

#include <string>
#include <vector>
#include <sstream> // istringstream

class Action
{
    public:
        Action(std::string name);
        virtual ~Action();
        const std::string id;
        void pushParam(std::string value);
        std::string popStrParam();
        int popIntParam();
    protected:
    private:
        std::vector <std::string> _params;
};

#endif // ACTION_H
