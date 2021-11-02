//
// Created by ncpd on 20-10-2021.
//


#include "src/Final/timeKeeper.h"
#include "src/Final/syncMaster.h"
#include "src/Final/syncSlave.h"
#include <thread>








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
  std::this_thread::sleep_for(std::chrono::milliseconds(60000));
    S.keeperS.resetTime();
    S.setSyncReq(M.syncReq_msg());
    S.syncAcpt();
   // std::this_thread::sleep_for(std::chrono::milliseconds(2));
    M.TS2();
    M.TS3();
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    S.TS23Recived(M.ts23[0], M.ts23[1]);
    //t = S.adjustClock( S.clockOffset(), S.roundTripTime());

    S.print();
    y = M.keeper.getTime();
    u = S.keeperS.getTime();
    o = S.adjustClock(S.clockOffset(), S.roundTripTime());
    p = M.keeper.getTime();
    std::cout<<"Master: "<<y<<std::endl;
    std::cout<<"Slave: "<<u<<std::endl;
    std::cout<<"Slave adjust: "<<o<<std::endl;
    std::cout<<"Master: "<<p<<std::endl;
    std::cout<<"Diff mellem salve og master: "<<o-p<<std::endl;




    return 0;
}

