//
// Created by Martin on 29-10-2021.
//
#include "timeKeeper.h"
#include "syncSlave.h"


Slave::Slave() : ts1234{0,0,0,0} {
}
void Slave::setSyncReq(std::string syncMsg) {
    syncReqR = syncMsg;
}
void Slave::TS1() {
    ts1234[0] = keeperS.getTime();
    //std::cout<<TS2<<std::endl;
}

void Slave::syncAcpt()  {
    if (syncReqR == "101001 REQ slave time 001010"){
        TS1();
    }
}

void Slave::TS4() {
    ts1234[3] = keeperS.getTime();
    //std::cout<<TS2<<std::endl;
}

void Slave::TS23Recived( long long TS2, long long TS3) {
    TS4();
    ts1234[1] = TS2;
    ts1234[2] = TS3;
}

long long  Slave::roundTripTime() {
    long long  roundTripTime;
    roundTripTime=((ts1234[3]-ts1234[0])-(ts1234[2]-ts1234[1]));
    return roundTripTime;
}
void Slave::print() {
    for (int i ; i < 4; i++) {
        std::cout << ts1234[i] << " ";
    }
    std::cout<<""<<std::endl;
    std::cout<<"round trip time: ";
    std::cout<<roundTripTime();
}

