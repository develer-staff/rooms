#ifndef TIMER_H
#define TIMER_H

#if defined(_WIN32) || defined(ming)
    #define WINDOWS
#else
    #define POSIX
#endif

#ifdef WINDOWS
    #include <windows.h>
#else
    #include <sys/time.h>
#endif

class Timer
{
public:
    Timer();

    void start();
    int elapsed();
    bool isRunning();
    void reset();

private:
    double getSeconds();
    int getMilliseconds(double seconds);

private:
    double _start_time;
};

#endif // TIMER_H
