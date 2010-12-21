#ifndef ACTION_H
#define ACTION_H

#include <string> //std::string
#include <vector> //std::vector
#include <sstream> // std::istringstream

/*! \brief Action handler.
 *         It handles action and its params.
 */
class Action
{
    public:
        const std::string id;
    private:
        std::vector <std::string> params;
    public:
        Action(const std::string name);
        ~Action();
    public:
        void pushParam(const std::string value);
        std::string popStrParam();
        int popIntParam();
};

#endif // ACTION_H
