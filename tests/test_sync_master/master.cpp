//
// Created by Martin on 03-11-2021.
//

#include <iostream>
#include "timeKeeper.h"
#include "syncMaster.h"
#include "syncSlave.h"
#include "dataTransport.h"
#include <thread>
DataTransport dt;
Master M;

void test_send_syncReq(){

    char slave_1_Ip[] = "192.168.0.105";
    DataTransport dt(slave_1_Ip, PORT, true);
    // char* tmp_hostname = dt.GetHostname();
    dt.open_connection();
     uint8_t msgToSend[] = {255};
    dt.send(msgToSend, sizeof(msgToSend));
}
void checkForSyncAcpt(){
    uint8_t * bufPTR = nullptr;
    uint16_t size = 0;
    bufPTR = dt.GetBuffer(bufPTR, &size);
    if(dt.receive() > 0 && *bufPTR == 1) {
        M.TS2();
        //std::cout<<"NOICEeee";
    }
}

int main(){
    test_send_syncReq();
    checkForSyncAcpt();
    return 0;
}