#include "csmanager.h"

CsManager::CsManager()
{
}

bool CsManager::startCutscene(const std::string csPath)
{
    CsParser p;
    if (!p.parse(csPath)){
        logger.write("Parser error: "+p.getErrorMessage(), Log::ERROR);
        return false;
    }

    objects = p.objects();
    steps = p.steps();
    current_step = p.startingSteps();
    logger.write("Cutscene loaded succesfully", Log::NOTE);
    return true;
}
