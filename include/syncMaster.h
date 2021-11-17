//
// Created by mc on 29-10-2021.
//

#ifndef CUSTOM_TIMEKEEPER_SYNCMASTER_H
#define CUSTOM_TIMEKEEPER_SYNCMASTER_H
#include <iostream>
#include "timeKeeper.h"
#include "udp_client.h"


#define SYNC_COMM_BUFFER_SIZE 256

class Sync_Master{
public:


    Sync_Master ();
    Sync_Master (char *host, bool is_ip);
    long long Get_Time();
    void Reset_Time();
    void TS2();
    void TS3();
    void SyncReq_and_accept();
    void Send_TS23();
    bool Wait_for_Sync_OK();


protected:

private:
    long long unsigned ts23[2];
    TimeKeeper keeper;
    UDP_client dt;
    uint8_t comm_buffer[SYNC_COMM_BUFFER_SIZE]{};

};







#endif //CUSTOM_TIMEKEEPER_SYNCMASTER_H
