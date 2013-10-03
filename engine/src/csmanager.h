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
 * The class is a layer between the parser and the engine, it transforms
 * the parser generated data structure to something that the engine can use
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

    void setVisibleData(GuiDataVect v);

private:
    void setInitialVisibleData();//TODO aggiungi all'engine
    SequentialAnimation *walkStep(std::string stepName);
    void updateAnimatedObject(const std::string &object_name, CsState state);

private:
    std::map<std::string, CsObject> animated_objects;
    std::map<std::string, CsStep> steps;
    std::vector<std::string> initial_steps;

    GuiDataVect visible_data;

    std::vector<Animation *> animations_garbage;
};

#endif // CSMANAGER_H
