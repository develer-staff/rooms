#ifndef LOG_H
#define LOG_H

#include <string> //std::string
#include <fstream> //std::ofstream
#include <time.h> //time()

class Log
{
    public:
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
        Log(std::string filename = "rooms.log", Log::Level log_type = NOTE);
        virtual ~Log();
    public:
        void write(std::string text, Log::Level log_type);
};

#endif // LOG_H
