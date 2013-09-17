#include "timer.h"

Timer::Timer() :
    _start_time(0)
{
}

void Timer::start()
{
    _start_time = getSeconds();
}

int Timer::elapsed()
{
    if (!isRunning())
        return 0;
    return getMilliseconds(getSeconds() - _start_time);
}

bool Timer::isRunning()
{
    if (_start_time != 0)
        return true;
    return false;
}

void Timer::reset()
{
    _start_time = 0;
}

double Timer::getSeconds()
{
#ifdef WINDOWS
    return static_cast<double>(GetTickCount())/1000.0;
#else
    timeval t;
    gettimeofday(&t, 0);
    return (t.tv_sec) + (t.tv_usec/1000000.0);
#endif
}

int Timer::getMilliseconds(double seconds)
{
    return int(seconds*1000);
}
