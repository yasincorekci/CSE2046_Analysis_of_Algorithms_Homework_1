
#ifndef __TIMER_H
#define __TIMER_H

#include <chrono>

class Timer
{
public:
    Timer();

    void start();
    void stop();
    double elapsed();
    double elapsedInMicroSeconds();
    double elapsedInMilliSeconds();
    double elapsedInSeconds();

private:
    std::chrono::time_point<std::chrono::system_clock> start_time;
    std::chrono::time_point<std::chrono::system_clock> end_time;
    bool is_running;
    bool is_started;
};

#endif

