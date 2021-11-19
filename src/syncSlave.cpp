//
// Created by Martin on 29-10-2021.
//
#include "../include/timeKeeper.h"
#include "../include/syncSlave.h"
#define PORT 1696
#define SyncReq 0xFF // tallet 255 = "1111 1111" for anmodning om sync
#define SyncAcpt 0x01 // tallet   1 = "0000 0001" for accept af sync
#define SyncDecline 0x81 // tallet   129 = "1000 0001" for decline af sync

/**********************************************************************************************************************
 * Static variables
 **********************************************************************************************************************/

static dt_type_t type = SYNC;


Sync_Slave::Sync_Slave() : dt(type, PORT), ts1234{0,0,0,0} {

}

void Sync_Slave::Reset_Time() {
    keeperS.resetTime();


}


void Sync_Slave::TS1() {
    ts1234[0] =keeperS.getTime();

}

void Sync_Slave::Sync_Check_And_Accept() {
    uint8_t *bufPTR = nullptr;
    uint16_t size = 0;
    uint8_t msg[] = {SyncAcpt};

    if (dt.receive(false) > 0) {
        bufPTR = dt.GetBuffer(bufPTR, &size);
        if (*bufPTR == SyncReq) {
            TS1();
            dt.send(msg, sizeof(msg));
        } else {
            std::cout<<" \033[1;31mSynchronization error due to wrong SyncReq CID \033[0m\n "<<" [Sync_Slave::Sync_Check_And_Accept] "<<std::endl;
        }
    }else{
        std::cout<<"Sync Error!!"<<std::endl;
    }
}

void Sync_Slave::Recive_TS23(){
    long long unsigned int *bufPTR = nullptr;
    uint8_t size = 0;
    if (dt.receive(false) > 0) {
        TS4();
        bufPTR = dt.GetBuffer(bufPTR, &size);
}
    for (int i = 0; i < size; i++) {
        ts1234[1]= *bufPTR;
    }
    bufPTR++;
    for (int i = 0; i < size; i++) {
        ts1234[2]= *bufPTR;
    }

}

void Sync_Slave::TS4() {
   ts1234[3] = keeperS.getTime();

}


unsigned int Sync_Slave::roundTripTime() {
    unsigned int roundTripTime;
    auto  ts1 = (long long)ts1234[0];
    auto  ts2 = (long long)ts1234[1];
    auto  ts3 = (long long)ts1234[2];
    auto  ts4 = (long long)ts1234[3];
    roundTripTime=((ts4-ts1)-(ts3-ts2));
    return roundTripTime;
}

long long  Sync_Slave::clockOffset() {
    long long  offset;
    auto  ts1 = (long long)ts1234[0];
    auto  ts2 = (long long)ts1234[1];
    auto  ts3 = (long long)ts1234[2];
    auto  ts4 = (long long)ts1234[3];
    offset=(((ts2-ts1)+(ts3-ts4))/2);
    return offset;
}

bool Sync_Slave::Check_Sync_OK(){
    bool flag = true;
    uint8_t msgAccpt[] = {SyncAcpt};
    uint8_t msgDecline[] = {SyncDecline};


    if (roundTripTime()<RTTallowed){
        dt.send(msgAccpt, sizeof(msgAccpt));
    }

    else {
        dt.send(msgDecline, sizeof(msgDecline));
        flag = false;
    }
    return flag;
}

long long Sync_Slave::adjustClock(long long CO){
    long long newtime;
    newtime=CO+keeperS.getTime();
    return newtime;
}


void Sync_Slave::print() {
    std::cout<<"_________________________________"<<std::endl;
    std::cout<<"TS1:                        " << ts1234[0] <<" µs "<<std::endl;
    std::cout<<"TS2:                   " << ts1234[1] <<" µs "<<std::endl;
    std::cout<<"TS3:                   " << ts1234[2] <<" µs "<<std::endl;
    std::cout<<"TS4:                      " << ts1234[3] <<" µs "<<std::endl;
    std::cout<<"---------------------------------"<<std::endl;
    std::cout<<"Round trip time:          " <<roundTripTime() <<" µs"<<std::endl;
    std::cout<<"Clock offset:          " <<clockOffset()<<" µs"<<std::endl;

}

