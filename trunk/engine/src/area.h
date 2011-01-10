/**
 * \file
 * <!--
 * Copyright 2010,2011 Daniele Maccioni
 * All rights reserved.
 * -->
 *
 * \version $Id: area.h $
 * \author Daniele Maccioni <gendoikari@develer.com>
 */


#ifndef AREA_H
#define AREA_H

#include <string> //std::string

/** \brief The Area class is a rectangular hot-spot.
 *
 * An area has a rectangular shape and an event. When area is clicked, the event may happen.
 */
class Area
{
    public:
        ///Area id. It must be unique.
        const std::string id;
    protected:
        float _x;
        float _y;
        float _width;
        float _height;
        std::string _event;
    public:
        /// Creates an area with an id.
        Area(const std::string name);
        virtual ~Area();
    public:
        /// Set area size through normalized coordinates.
        void size(const float x, const float y, const float width, const float height);
        /// Get normalized x.
        float x() const;
        /// Get normalized y.
        float y() const;
        /// Get normalized width.
        float w() const;
        /// Get normalized height.
        float h() const;
        /// Get event id.
        std::string event() const;
        /// Set event id.
        void setEvent(const std::string event);
};

#endif // AREA_H
