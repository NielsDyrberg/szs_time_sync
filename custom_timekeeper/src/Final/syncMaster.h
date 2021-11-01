//
// Created by Martin on 29-10-2021.
//

#ifndef CUSTOM_TIMEKEEPER_SYNCMASTER_H
#define CUSTOM_TIMEKEEPER_SYNCMASTER_H
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <cmath>
#include "timeKeeper.h"




class Master{
public:
    Master ();
    long long ts23[2];

    TimeKeeper keeper;
    std::string syncReq_msg();
    void TS2();
    void TS3();

    void print();
protected:
private:

};







#endif //CUSTOM_TIMEKEEPER_SYNCMASTER_H
