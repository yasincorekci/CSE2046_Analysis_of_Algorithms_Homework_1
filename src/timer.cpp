#include "timer.h"

Timer::Timer() : is_started(false), is_running(false)
{
}

void Timer::start()
{
    start_time = std::chrono::system_clock::now();
    is_running = true;
    is_started = true;
}

void Timer::stop()
{
    end_time = std::chrono::system_clock::now();
    is_running = false;
}

double Timer::elapsed()
{
    std::chrono::time_point<std::chrono::system_clock> time;

    if (!is_started)
        return 0.0;

    if (is_running) {
        time = std::chrono::system_clock::now();
    }
    else {
        time = end_time;
    }

    return (double) std::chrono::duration_cast<std::chrono::nanoseconds>(time - start_time).count();
}

double Timer::elapsedInMicroSeconds()
{
    return elapsed() / 1000.0;
}

double Timer::elapsedInMilliSeconds()
{
    return elapsed() / 1000000.0;
}

double Timer::elapsedInSeconds()
{
    return elapsed() / 1000000000.0;
}
