//
// Created by Martin on 29-10-2021.
//

#ifndef CUSTOM_TIMEKEEPER_SYNCSLAVE_H
#define CUSTOM_TIMEKEEPER_SYNCSLAVE_H
#include "timeKeeper.h"
#include "udp_server.h"


class Timekeeper_Slave {

public:
    Timekeeper_Slave();
    TimeKeeper keeperS;
    UDP_server dt;
    void TS1();
    void Sync_Check_And_Accept();
    void TS4();
    long long roundTripTime();
    long long clockOffset();
    bool Check_Sync_OK();
    long long adjustClock( long long CO);
    void print();
    void Recive_TS23();
protected:

private:
    long long unsigned ts1234[4];





};
















#endif //CUSTOM_TIMEKEEPER_SYNCSLAVE_H
