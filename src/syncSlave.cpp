//
// Created by Martin on 29-10-2021.
//
#include "../include/timeKeeper.h"
#include "../include/syncSlave.h"
#define PORT 1696
#define SyncReq 0xFF // tallet 255 = "1111 1111" for anmodning om sync
#define SyncAcpt 0x01 // tallet   1 = "0000 0001" for accept af sync

long long newtime;
Timekeeper_Slave::Timekeeper_Slave() : dt(PORT), ts1234{0,0,0,0,0} {

}

void Timekeeper_Slave::TS1() {
    int k = 138;
    ts1234[0] = keeperS.getTime();
    //std::cout<<TS2<<std::endl;
}

void Timekeeper_Slave::Sync_Check_And_Accept() {
    uint8_t *bufPTR = nullptr;
    uint16_t size = 0;
    uint8_t msg[] = {SyncAcpt};
    if (dt.receive(false) > 0) {
        bufPTR = dt.GetBuffer(bufPTR, &size);
        if (*bufPTR == SyncReq) {
            TS1();
            dt.send(msg, sizeof(msg));
        } else {
            std::cout << "Sync Error" << std::endl;
        }
    }
}

void Timekeeper_Slave::Recive_TS23(){
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

void Timekeeper_Slave::TS4() {
    ts1234[3] = keeperS.getTime();
    //std::cout<<TS2<<std::endl;
}
void Timekeeper_Slave::TS44() {
    ts1234[4] = keeperS.getTime();
    //std::cout<<TS2<<std::endl;
}



long long  Timekeeper_Slave::roundTripTime() {
    long long  roundTripTime;
    auto  ts1 = (long long)ts1234[0];
    auto  ts2 = (long long)ts1234[1];
    auto  ts3 = (long long)ts1234[2];
    auto  ts4 = (long long)ts1234[3];
    roundTripTime=((ts4-ts1)-(ts3-ts2))/2;
    return roundTripTime;
}

long long  Timekeeper_Slave::clockOffset() {
    long long  offset;
    auto  ts1 = (long long)ts1234[0];
    auto  ts2 = (long long)ts1234[1];
    auto  ts3 = (long long)ts1234[2];
    auto  ts4 = (long long)ts1234[3];
    offset=(((ts2-ts1)+(ts3-ts4))/2);
   // offset=(((ts1234[1]-ts1234[0])+(ts1234[2]-ts1234[3]))/2);
    return offset;
}

long long Timekeeper_Slave::adjustClock(long long CO){
    newtime=CO+keeperS.getTime();
    return newtime;
}




void Timekeeper_Slave::print() {
    std::cout<<"_________________________________"<<std::endl;
    std::cout<<"TS1:                        " << ts1234[0] <<" µs "<<std::endl;
    std::cout<<"TS2:                   " << ts1234[1] <<" µs "<<std::endl;
    std::cout<<"TS3:                   " << ts1234[2] <<" µs "<<std::endl;
    std::cout<<"TS4:                      " << ts1234[3] <<" µs "<<std::endl;
    /*
    int j = 1;
    for (int i=0; i <= 3; i++) {
        if (i==3){
            std::cout<<"TS"<<j <<":" << ts1234[i] <<" "<<std::endl;
        } else{
        std::cout<<"TS"<<j <<":" << ts1234[i] <<", ";
    }
        j++;
    }*/
    std::cout<<"---------------------------------"<<std::endl;
    std::cout<<"Round trip time:          " <<roundTripTime() <<" µs"<<std::endl;
    std::cout<<"Clock offset:          " <<clockOffset()<<" µs"<<std::endl;

}

