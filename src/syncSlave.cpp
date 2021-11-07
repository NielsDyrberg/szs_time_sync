//
// Created by Martin on 29-10-2021.
//
#include "../include/timeKeeper.h"
#include "../include/syncSlave.h"

long long newtime;
Slave::Slave() : ts1234{0,0,0,0,0} {
}

void Slave::TS1() {
    int k = 138;
    ts1234[0] = keeperS.getTime()+k;
    //std::cout<<TS2<<std::endl;
}



void Slave::TS4() {
    ts1234[3] = keeperS.getTime();
    //std::cout<<TS2<<std::endl;
}
void Slave::TS44() {
    ts1234[4] = keeperS.getTime();
    //std::cout<<TS2<<std::endl;
}

void Slave::TS23Recived( long long TS2, long long TS3) {


    ts1234[1] = TS2;
    ts1234[2] = TS3;

}

long long  Slave::roundTripTime() {
    long long  roundTripTime;
    auto  ts1 = (long long)ts1234[0];
    auto  ts2 = (long long)ts1234[1];
    auto  ts3 = (long long)ts1234[2];
    auto  ts4 = (long long)ts1234[3];
    roundTripTime=((ts4-ts1)-(ts3-ts2))/2;
    return roundTripTime;
}

long long  Slave::clockOffset() {
    long long  offset;
    auto  ts1 = (long long)ts1234[0];
    auto  ts2 = (long long)ts1234[1];
    auto  ts3 = (long long)ts1234[2];
    auto  ts4 = (long long)ts1234[3];
    offset=(((ts2-ts1)+(ts3-ts4))/2);
   // offset=(((ts1234[1]-ts1234[0])+(ts1234[2]-ts1234[3]))/2);
    return offset;
}

long long Slave::adjustClock(long long CO){
    newtime=CO+keeperS.getTime();
    return newtime;
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

