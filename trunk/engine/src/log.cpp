#include "log.h"

Log::Log(std::string file_name, Log::Level log_type)
{
    filename = file_name;
    level = log_type;
    std::ofstream log_file;
    log_file.open(filename.c_str(), std::ios::out);
    log_file.close();
}

Log::~Log()
{

}

void Log::write(std::string text, Log::Level log_type)
{
    if (log_type <= level)
    {
        std::ofstream log_file;
        log_file.open(filename.c_str(), std::ios::out | std::ios::app);
        log_file << time(0) << ": " << text << '\n';
        log_file.close();
    }
}
