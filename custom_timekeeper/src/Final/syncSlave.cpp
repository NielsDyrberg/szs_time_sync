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
    if (syncReqR == "101001 REQ slave time 001010") {
        TS1();
    }

}

void Slave::TS4() {
    ts1234[3] = keeperS.getTime();
    //std::cout<<TS2<<std::endl;
}

void Slave::TS23Recived( long long TS2, long long TS3) {

    ts1234[1] = TS2;
    ts1234[2] = TS3;
    TS4();
}

long long  Slave::roundTripTime() {
    long long  roundTripTime;
    roundTripTime=((ts1234[3]-ts1234[0])-(ts1234[2]-ts1234[1]));
    return roundTripTime;
}

long long  Slave::clockOffset() {
    long long  offset;
    offset=(((ts1234[1]-ts1234[0])+(ts1234[2]-ts1234[3]))/2);
    return offset;
}

long long Slave::adjustClock(long long CO){
    long long newClock;
    newClock = CO+keeperS.getTime();
    return newClock;
}

void Slave::print() {
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

