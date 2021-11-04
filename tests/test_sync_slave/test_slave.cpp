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
Slave S;
void test_recv_two_longlong_int(){
    uint8_t * bufPTR = nullptr;
    uint16_t size = 0;

    if(dt.receive() > 0) {
        bufPTR = dt.GetBuffer(bufPTR, &size);
        for (int i = 0; i < size; i++) {
            std::cout << unsigned(*bufPTR) << std::endl;
            bufPTR++;
        }
    }
    std::cout << "Hello, World!" << std::endl;
}

void checkForSync(){
    uint8_t * bufPTR = nullptr;
    uint16_t size = 0;
    bufPTR = dt.GetBuffer(bufPTR, &size);
    if(dt.receive() > 0 && *bufPTR == 255) {
        S.TS1();
        //std::cout<<"NOICE";
        }
}

void test_send_syncReq(){

    char MASTER[] = "192.168.0.104";
    DataTransport dt(MASTER, PORT, true);
    // char* tmp_hostname = dt.GetHostname();
    dt.open_connection();
    uint8_t msgToSend[] = {1};
    dt.send(msgToSend, sizeof(msgToSend));
}


int main(){
    //test_recv_two_longlong_int();
    checkForSync();
    return 0;
}