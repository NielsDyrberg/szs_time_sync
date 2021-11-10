//
// Created by Martin on 29-10-2021.
//

#include "../include/syncMaster.h"
#define PORT 1695
#define SyncReq 0xFF // tallet 255 = "1111 1111" for anmodning om sync
#define SyncAcpt 0x01 // tallet   1 = "0000 0001" for accept af sync
#define S1_ip "192.168.0.101"
#define S2_ip "192.168.0.102"
#define S3_ip "192.168.0.103"
#define S4_ip "192.168.0.104"
#define S5_ip "192.168.0.104"
char slaveIP[14] = S3_ip;


TimeKeeper_Master::TimeKeeper_Master() : dt(slaveIP, PORT, true ),   ts23{0,0,0}{


}

std::string TimeKeeper_Master::syncReq_msg() {

    std::string syncReq = "101001 REQ slave time 001010";
    return syncReq;
}

void TimeKeeper_Master::TS2() {
    ts23[0] = keeper.getTime();
    //std::cout<<TS2<<std::endl;


}

void TimeKeeper_Master::TS3() {
    unsigned int k = 40;
    ts23[1] = keeper.getTime()+k;
    //std::cout<<TS3<<std::endl;


}
void TimeKeeper_Master::TS33() {
    ts23[2] = keeper.getTime();
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
            //std::cout<<"JEG ER HER bare rolig"<<std::endl;

        }

    }
}
void TimeKeeper_Master::Send_TS23(){
    TS3();
    long long unsigned int msg[] ={ts23[0], ts23[1]};
    dt.send(msg, sizeof(msg));
}

/*void Master::print() {
    std::cout<<ts23[0] << " ";
    std::cout<<ts23[1] << std::endl;
}*/





/*int timeDiff::calcTimeDiff(int TS1, int TS2, int TS3, int TS4) {

    int roundTripTime;
    int clockDelay;

    roundTripTime=((TS4-TS1)-(TS3-TS2));
    clockDelay = abs((((TS2-TS1)+(TS3-TS4))/2));


    return 0;
}
 */

