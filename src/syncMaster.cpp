//
// Created by Martin on 29-10-2021.
//

#include "../include/syncMaster.h"
#define PORT 1696
#define SyncReq 0xFF // tallet 255 = "1111 1111" for anmodning om sync
#define SyncAcpt 0x01 // tallet   1 = "0000 0001" for accept af sync
#define SyncDecline 0x81 // tallet   129 = "1000 0001" for decline af sync


#define S1_ip "192.168.0.101"
#define S2_ip "192.168.0.102"
#define S3_ip "192.168.0.103"
#define S4_ip "192.168.0.104"
#define S5_ip "192.168.0.105"
#define S6_ip "192.168.0.106"
char slaveIP[14] = S3_ip;


TimeKeeper_Master::TimeKeeper_Master() : dt(slaveIP, PORT, true ),   ts23{0,0}{
}


void TimeKeeper_Master::TS2() {
    ts23[0] = keeper.getTime();
   // std::cout<<ts23[0]<<std::endl;

}

void TimeKeeper_Master::TS3() {
    unsigned int k = 40;
    ts23[1] = keeper.getTime();// konstant er påsat her!OBS
    //std::cout<<TS3<<std::endl;

}

void TimeKeeper_Master::SyncReq_and_accept(){
    uint8_t * bufPTR = nullptr;
    uint16_t size = 0;
    uint8_t msg[] = {0xFF};
    if(dt.send_and_receive(msg, sizeof(msg)) > 0) {
        bufPTR = dt.GetBuffer(bufPTR, &size);
        if (*bufPTR == SyncAcpt){
            TS2();
        }

    }
}
void TimeKeeper_Master::Send_TS23(){
    TS3();
    long long unsigned int msg[] ={ts23[0], ts23[1]};
    dt.send(msg, sizeof(msg));
}

bool TimeKeeper_Master::Wait_for_Sync_OK(){
    bool check = false;
    long long unsigned int *bufPTR = nullptr;
    uint8_t size = 0;
    if (dt.receive(false) > 0) {
        bufPTR = dt.GetBuffer(bufPTR, &size);
        if (*bufPTR == SyncAcpt) {
            check = true;
        }
}
    return check ;
}



