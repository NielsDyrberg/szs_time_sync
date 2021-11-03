//
// Created by ncpd on 21-10-2021.
//

#include "../include/timeKeeper.h"

  TimeKeeper::TimeKeeper (){
    start_time = std::chrono::steady_clock::now();
}


void TimeKeeper::resetTime(){

    start_time = std::chrono::steady_clock::now();


}

long long int TimeKeeper::getTime() {

    //retuner clock µs lige nu.
    long long timeNow;
    auto updateTid = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(updateTid-start_time);
    timeNow = diff.count();
    //std::cout<<timeNow<<std::endl;

    return timeNow;
}
