#ifndef CSMANAGER_H
#define CSMANAGER_H
#include "log.h"
#include "csparser.h"
#include "animation.h"

#include <string>

extern Log logger;

class CsManager
{
public:
    CsManager();

    bool startCutscene(const std::string csPath);

private:
    std::map<std::string, CsObject> objects;
    std::map<std::string, CsStep> steps;
    std::vector<std::string> current_step;
};

#endif // CSMANAGER_H
