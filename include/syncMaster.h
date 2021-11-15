//
// Created by Martin on 29-10-2021.
//

#ifndef CUSTOM_TIMEKEEPER_SYNCMASTER_H
#define CUSTOM_TIMEKEEPER_SYNCMASTER_H
#include <iostream>
#include "timeKeeper.h"
#include "udp_client.h"




class TimeKeeper_Master{
public:


    TimeKeeper_Master ();

    TimeKeeper keeper;
    UDP_client dt;
    void TS2();
    void TS3();
    void SyncReq_and_accept();
    void Send_TS23();
    bool Wait_for_Sync_OK();


protected:

private:
    long long unsigned ts23[2];

};







#endif //CUSTOM_TIMEKEEPER_SYNCMASTER_H
