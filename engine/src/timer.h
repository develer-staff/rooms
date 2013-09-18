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

/**
 * \brief A Timer class
 *
 * The timer doesn't have a timeout value,
 * it simply count the time since the start
 */
class Timer
{
public:
    Timer();

    /// Starts the timer
    void start();
    /// Returns milliseconds elapsed since the start
    int elapsed();
    /// Returns true if the timer is running
    bool isRunning();
    /// Stops the timer and resets it
    void reset();

private:
    double getSeconds();
    int getMilliseconds(double seconds);

private:
    double _start_time;
};

#endif // TIMER_H
