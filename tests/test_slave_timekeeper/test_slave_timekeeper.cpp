//
// Created by Martin on 10-11-2021.
//

#include <iostream>

#include "timeKeeper.h"
#include "syncSlave.h"



int main(){
    Timekeeper_Slave S;
    S.Sync_Check_And_Accept();
    S.Recive_TS23();
    //S.print();


    return 0;
}