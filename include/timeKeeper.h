//
// Created by Martin on 21-10-2021.
//
#ifndef CUSTOM_TIMEKEEPER_TIMEKEEPER_H
#define CUSTOM_TIMEKEEPER_TIMEKEEPER_H
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <cmath>



class TimeKeeper{

public:

    TimeKeeper();
    void resetTime();
    long long getTime();

protected:


private:
    std::chrono::time_point<std::chrono::steady_clock> start_time;

};
#endif //CUSTOM_TIMEKEEPER_TIMEKEEPER_H