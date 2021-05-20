#include "include/timer.h"

Timer::Timer(double interval) {

    this->interval = interval;
    ResetTime();
}
bool Timer::GetUpdate() {
  //  printf("Time: %f \n", GetTime());
    if (GetTime() >= interval) {

        ResetTime();
        return true;
    }

    return false;
}

void Timer::ResetTime() {
    start_point = std::chrono::steady_clock::now();
}

double Timer::GetTime() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_point).count()/1000.0f;
}