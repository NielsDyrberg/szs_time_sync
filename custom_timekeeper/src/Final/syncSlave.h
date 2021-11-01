//
// Created by Martin on 29-10-2021.
//

#ifndef CUSTOM_TIMEKEEPER_SYNCSLAVE_H
#define CUSTOM_TIMEKEEPER_SYNCSLAVE_H
#include "timeKeeper.h"
#include <chrono>

class Slave {
public:
    Slave();
    TimeKeeper keeperS;
    void setSyncReq(std::string syncMsg);
    void syncAcpt();
    void TS1();
    void TS23Recived( long long TS2, long long TS3);
    void TS4();
    long long roundTripTime();
    void print();

protected:
    long long ts1234[4];
private:
    std::string syncReqR;




};
















#endif //CUSTOM_TIMEKEEPER_SYNCSLAVE_H
