/**
 * \file
 * <!--
 * Copyright 2010,2011 Daniele Maccioni
 * All rights reserved.
 * -->
 *
 * \version $Id: action.h $
 * \author Daniele Maccioni <gendoikari@develer.com>
 */


#ifndef ACTION_H
#define ACTION_H

#include <string> //std::string
#include <vector> //std::vector
#include <sstream> // std::istringstream

/** \brief The Action class is used to handle event actions.
 *
 * An action has a type and a stack of parameters.
 * Engine will use these parameters to obtain action informations.
 */
class Action
{
    public:
        /// It's the action type.
        const std::string id;
    private:
        std::vector <std::string> params;
    public:
        /// Creates an action of the given type.
        Action(const std::string name);
        ~Action();
    public:
        /// Pushes a parameter in the stack.
        void pushParam(const std::string value);
        /// Pops a string parameter from stack.
        std::string popStrParam();
        /// Pops an int parameter from stack.
        int popIntParam();
};

#endif // ACTION_H
