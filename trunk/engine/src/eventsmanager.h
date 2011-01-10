/**
 * \file
 * <!--
 * Copyright 2010,2011 Daniele Maccioni
 * All rights reserved.
 * -->
 *
 * \version $Id: eventsmanager.h $
 * \author Daniele Maccioni <gendoikari@develer.com>
 */

#ifndef EVENTSMANAGER_H
#define EVENTSMANAGER_H

#include <string> //std::string
#include <map> //std::map
#include <vector> //std::vector
#include <utility> //std::pair

class Event;
class Action;

using std::string;

/** \brief The EventsManager class handles events.
 *
 * Creates and destroys events.
 */
class EventsManager
{
    private:
        std::map <string, Event *> events;
        //ATTENTION: var names that begin with '!' identify internal vars.
        std::map <string, int> _vars;
    public:
        EventsManager();
        ~EventsManager();
    public:
        /// Creates an Event and returns it.
        Event *addEvent(const string name);
        /// Adds a created Event to the internal events list.
        void addEvent(Event *event);
        /// Returns an event from id.
        Event *event(const string name);
        /// Gets the actions related to an event.
        std::vector <Action *> actionsForEvent(const string name);
        /// Sets/creates a variable with a value.
        void setVar(const string name, const int value);
        /// Gets a variable value.
        int var(const string name) const;
        /// Checks if a list of var requirements is satisfied.
        bool checkVarReqs(const std::vector <std::pair <string, int> > reqs) const;
};

#endif // EVENTSMANAGER_H
