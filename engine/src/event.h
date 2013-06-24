/**
 * \file
 * <!--
 * Copyright 2010,2011 Daniele Maccioni
 * All rights reserved.
 * -->
 *
 * \version $Id: event.h $
 * \author Daniele Maccioni <gendoikari@develer.com>
 */


#ifndef EVENT_H
#define EVENT_H

#include <string> //std::string
#include <vector> //std::vector
#include <utility> //std::pair std::make_pair

using std::string;

class Action;

/** \brief The Event class handles events informations, such as requirements and actions.
 *
 * An event is an action list linked to a list of requirements.
 * An event happens only if requirements are satisfied.
 */
class Event
{
    public:
        /// Event id. It must be unique.
        const std::string id;
    private:
        std::vector <Action *> _actions;
        std::vector <std::pair <string, string> > item_reqs;
        std::vector <std::pair <string, int> > var_reqs;
    public:
        /// Creates an event with given id.
        Event(const string name);
        ~Event();
    public:
        /// Adds a new action to the event.
        Action *addAction(const string name);
        /// Gets the action list.
        std::vector <Action *> actions() const;
        /// Adds an item requirement to the event.
        void addItemReq(const string name, const string room);
        /// Adds a var requirement to the event.
        void addVarReq(const string name, const int value);
        /// Gets the item requirements list.
        std::vector <std::pair <string, string> > itemReqs() const;
        /// Gets the var requirements list.
        std::vector <std::pair <string, int> > varReqs() const;
};

#endif // EVENT_H
