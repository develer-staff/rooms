/**
 * \file
 * <!--
 * Copyright 2010,2011 Daniele Maccioni
 * All rights reserved.
 * -->
 *
 * \version $Id: dialog.h $
 * \author Daniele Maccioni <gendoikari@develer.com>
 */


#ifndef DIALOG_H
#define DIALOG_H

#include "action.h"
#include "event.h"
#include "log.h"

#include <string> //std::string
#include <map> //std::map
#include <utility> //std::pair

using std::string;

extern Log logger;

/** \brief The DialogStep struct represents a dialogue node.
 *
 */
struct DialogStep
{
    string id;
    Event *event;
    string text;
    string avatar;
    std::vector< std::pair<string, string> > links; //step id, choice text
};

/** \brief The Dialog class manages the dialog structure.
 *
 * A dialog is an arc-oriented graph.
 */
class Dialog
{
    public:
        /// Dialogue id. It must be unique.
        const string id;
    private:
        const string begin_step;
        DialogStep *current_step;
        std::map <string, DialogStep> steps;
    public:
        /** \brief Creates a dialog with given name and start step.
         *
         * \param name      It's the id.
         * \param start     It's the starting step id.
         */
        Dialog(const string name, const string start);
        ~Dialog();
    public:
        /// Resets the dialog: current step is replaced with starting step.
        void reset();
        /** \brief Jumps to a given step.
         *
         * \param step_name Jump destination.
         * \return It returns the action list related to destination step.
         */   std::vector <Action *> jump(const string step_name);
        /// Gets current step text.
        string text() const;
        /// Adds a step to the dialogue.
        DialogStep *addStep(const string name, const string text);
        /** \brief Adds a link to a step.
         *
         * \param name      It's the step id.
         * \param dest      It's the link destination step.
         * \param text      It's the choice text.
         */
        void addLink(const string name, const string dest, const string text);
        /// Gets a dialog step.
        DialogStep *step(const string name);
        /// Gets the action list of the current step.
        std::vector <Action *> actions();
        /** \brief Gets the link list of the current step.
         *
         * \return It's a vector of pairs. The firs element is the step id. The second element is the step choice text.
         */
        std::vector< std::pair<string, string> > links();
};

#endif // DIALOG_H
