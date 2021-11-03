//
// Created by ncpd on 20-10-2021.
//


#include "timeKeeper.h"
#include "syncMaster.h"
#include "syncSlave.h"
#include "dataTransport.h"
#include <thread>

void test_dt(){

}

int main() {
    long long t;
    long long y;
    long long u;
    long long o;
    long long p;
//Master Ma;
//TimeKeeper tk;
Master M;
Slave S;
//tk.resetTime();
    M.keeper.getTime();
    S.keeperS.getTime();
    sleep(1);
    M.keeper.resetTime();
   std::this_thread::sleep_for(std::chrono::milliseconds(1032));
    S.keeperS.resetTime();
    S.setSyncReq(M.syncReq_msg());
    S.syncAcpt();
   std::this_thread::sleep_for(std::chrono::milliseconds(2));
    M.TS2();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    M.TS3();
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    S.TS23Recived(M.ts23[0], M.ts23[1]);
    //t = S.adjustClock( S.clockOffset(), S.roundTripTime());

    S.print();
    y = M.keeper.getTime();
    u = S.keeperS.getTime();
    o = S.adjustClock(S.clockOffset());
    p = M.keeper.getTime();
    std::cout<<"---------------------------------"<<std::endl;
    std::cout<<"Master time right now: "<<y<<" µs "<<std::endl;
    std::cout<<"Slave time right now:     "<<u<<" µs "<<std::endl;
    std::cout<<"---------------------------------"<<std::endl;
    std::cout<<"Slave adjusted time:   "<<o<<" µs "<<std::endl;
    std::cout<<"Master time:           "<<p<<" µs "<<std::endl;
    std::cout<<"Diff salve/master:           "<<o-p<<" µs "<<std::endl;
    std::cout<<"_________________________________"<<std::endl;





    return 0;
}

