#ifndef CSMANAGER_H
#define CSMANAGER_H
#include "log.h"
#include "csparser.h"
#include "sequentialanimation.h"
#include "gui.h"

#include <string>

extern Log logger;

/**
 * \brief The CsManager class handles cutscenes
 *
 * It gets the cutscene from the parser and act as a conversion layer
 * between parser specific objects and something that the Engine can handle
 */
class CsManager
{
public:
    CsManager();
    ~CsManager();

    /**
     * \brief startCutscene parses the file and sets up the enviroment
     * \param csPath the cutscene file path
     * \return true if everything is ok, otherwise false
     */
    bool startCutscene(const std::string &csPath);

    /**
     * \brief getCurrentAnimations
     * \return a vector with the current animations
     * If the return vector is empty, the cutscene is finished
     */
    std::vector<SequentialAnimation *> getAnimations();

    ///Clean the cutscene enviroment
    void endCutscene();

    ///Get the cutscene visible data
    GuiDataVect getVisibleData();

    /// Updates the internal visible data representation
    void setVisibleData(GuiDataVect v);

private:
    void setInitialVisibleData();//TODO aggiungi all'engine
    SequentialAnimation *walkStep(std::string stepName);
    CsObject *animatedObject(const std::string &name);

private:
    std::vector<CsObject> animated_objects;
    std::map<std::string, CsStep> steps;
    std::vector<std::string> initial_steps;

    GuiDataVect visible_data;

    std::vector<Animation *> animations_garbage;
};

#endif // CSMANAGER_H
