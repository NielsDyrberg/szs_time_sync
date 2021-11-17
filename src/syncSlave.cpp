//
// Created by Martin on 29-10-2021.
//
#include "../include/timeKeeper.h"
#include "../include/syncSlave.h"
#define PORT 1696
#define SyncReq 0xFF // tallet 255 = "1111 1111" for anmodning om sync
#define SyncAcpt 0x01 // tallet   1 = "0000 0001" for accept af sync
#define SyncDecline 0x81 // tallet   129 = "1000 0001" for decline af sync




Sync_Slave::Sync_Slave() : dt(PORT), ts1234{0,0,0,0} {

}

void Sync_Slave::Reset_Time() {
    keeperS.resetTime();


}


void Sync_Slave::TS1() {
    int k = 138;
    ts1234[0] =keeperS.getTime();//keeperS.getTime();
    //std::cout<<"TS1: "<<ts1234[0]<<std::endl;

}

void Sync_Slave::Sync_Check_And_Accept() {
    uint8_t *bufPTR = nullptr;
    uint16_t size = 0;
    uint8_t msg[] = {SyncAcpt};

    if (dt.receive(false) > 0) {
        bufPTR = dt.GetBuffer(bufPTR, &size);
        if (*bufPTR == SyncReq) {
           // std::cout<<"Jeg har modtaget data"<<std::endl;
            TS1();
            dt.send(msg, sizeof(msg));
        } else {
           // std::cout << "Sync Error" << std::endl;
        }
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
    //std::cout<<TS2<<std::endl;
}


long long  Sync_Slave::roundTripTime() {
    long long  roundTripTime;
    auto  ts1 = (long long)ts1234[0];
    auto  ts2 = (long long)ts1234[1];
    auto  ts3 = (long long)ts1234[2];
    auto  ts4 = (long long)ts1234[3];
    roundTripTime=((ts4-ts1)-(ts3-ts2))/2;
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
    long long int RTTallowed = 1200;

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
    long long newtime=0;
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

