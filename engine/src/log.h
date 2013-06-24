/**
 * \file
 * <!--
 * Copyright 2010,2011 Daniele Maccioni
 * All rights reserved.
 * -->
 *
 * \version $Id: log.h $
 * \author Daniele Maccioni <gendoikari@develer.com>
 */


#ifndef LOG_H
#define LOG_H

#include <string> //std::string
#include <fstream> //std::ofstream
#include <time.h> //time()

/** \brief Simple log class.
 *
 * This class handles a simple log file.
 */
class Log
{
    public:
        /// Log level, from NONE (log nothing), to NOTE (log everything).
        enum Level
        {
            NONE,
            ERROR,
            WARNING,
            NOTE
        };
    private:
        std::string filename;
        Log::Level level;
    public:
        /// Creates log object with log filename and log level.
        Log(std::string filename = "rooms.log", Log::Level log_type = NOTE);
        virtual ~Log();
    public:
        /// Write a string in the log file. If log_type is bigger than log level, message is ignored.
        void write(std::string text, Log::Level log_type);
};

#endif // LOG_H
