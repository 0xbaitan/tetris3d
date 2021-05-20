#ifndef _TIMER_H_
#define _TIMER_H_

#include <chrono>
#include <stdio.h>
#define HOURS 0x00
#define MINUTES 0x01
#define SECONDS 0x02

typedef std::chrono::steady_clock::time_point TimePoint;

class Timer {
public:
    Timer(double interval);

    bool GetUpdate();

    ~Timer();

private:
    TimePoint start_point;
    double interval;

    double GetTime();
    void ResetTime();
};

#endif