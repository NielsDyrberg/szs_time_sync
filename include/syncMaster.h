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
#include "udp_client.h"
#define ip "192.168.0.103"




class TimeKeeper_Master{
public:


    TimeKeeper_Master ();

    long long unsigned ts23[3];

    TimeKeeper keeper;
    UDP_client dt;
    std::string syncReq_msg();
    void TS2();
    void TS3();
    void TS33();
    void SyncReq_and_accept();
    void Send_TS23();


protected:

private:

};







#endif //CUSTOM_TIMEKEEPER_SYNCMASTER_H
