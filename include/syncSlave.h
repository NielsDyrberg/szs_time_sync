//
// Created by Martin on 29-10-2021.
//

#ifndef CUSTOM_TIMEKEEPER_SYNCSLAVE_H
#define CUSTOM_TIMEKEEPER_SYNCSLAVE_H
#include "timeKeeper.h"
#include "udp_server.h"
#include <chrono>
#include <cmath>
class Timekeeper_Slave {

public:
    Timekeeper_Slave();
    TimeKeeper keeperS;
    UDP_server dt;
    void TS1();
    void Sync_Check_And_Accept();

    void TS4();
    void TS44();
    long long roundTripTime();
    long long clockOffset();
    bool Check_Sync_OK();
    long long adjustClock( long long CO);
    void print();
    unsigned long long ts1234[5];
    void Recive_TS23();
protected:

private:

    std::string syncReqR;




};
















#endif //CUSTOM_TIMEKEEPER_SYNCSLAVE_H
