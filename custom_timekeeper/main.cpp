//
// Created by ncpd on 20-10-2021.
//


#include "src/Final/timeKeeper.h"
#include "src/Final/syncMaster.h"
#include "src/Final/syncSlave.h"
#include <thread>








int main() {
//Master Ma;
//TimeKeeper tk;
Master M;
Slave S;
//tk.resetTime();
    M.keeper.resetTime();
    S.keeperS.resetTime();
    sleep(1);
    //tk.getTime();
   //sleep(1);
    S.setSyncReq(M.syncReq_msg());
    S.syncAcpt();
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    M.TS2();
    M.TS3();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    S.TS23Recived(M.ts23[0], M.ts23[1]);
    S.roundTripTime();
    S.print();
    //tk.getTime();
   // sleep(1);
  //  td.TS3();
  //  sleep(1);
//std::cout<<Ma.ts23[0]<<std::endl;
//std::cout<<Ma.ts23[0]<<std::endl;





    return 0;
}

