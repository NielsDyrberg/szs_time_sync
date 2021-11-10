//
// Created by Martin on 10-11-2021.
//

#include <iostream>
#include <unistd.h>
#include "timeKeeper.h"
#include "syncMaster.h"



int main(){
    TimeKeeper_Master M;
    M.SyncReq_and_accept();
    M.Send_TS23();
    return 0;
}