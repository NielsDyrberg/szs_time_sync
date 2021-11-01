//
// Created by Martin on 29-10-2021.
//

#include "syncMaster.h"






Master::Master() : ts23{0,0}{
}

std::string Master::syncReq_msg() {

    std::string syncReq = "101001 REQ slave time 001010";
    return syncReq;
}

void Master::TS2() {
    ts23[0] = keeper.getTime();
    //std::cout<<TS2<<std::endl;


}

void Master::TS3() {
    ts23[1] = keeper.getTime();
    //std::cout<<TS3<<std::endl;


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

