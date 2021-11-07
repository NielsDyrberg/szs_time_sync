//
// Created by Martin on 03-11-2021.
//

#include <iostream>
#include "timeKeeper.h"
#include "syncMaster.h"
#include "syncSlave.h"
#include "dataTransport.h"
#include <bcm2835.h>
#include <thread>
#define PIN RPI_V2_GPIO_P1_40 //gpio 17
DataTransport dt;
TimeKeeper T;
Master M;

char slave_1_Ip[] = "192.168.0.101";

int Test_setPinLow(){
    if (!bcm2835_init())
        return 1;

    // Set the pin to be an output
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(PIN, LOW);
    bcm2835_delay(500);
    return 0;
}
int Test_setPinHIGH(){
    if (!bcm2835_init())
        return 1;

    // Set the pin to be an output
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(PIN, HIGH);
    bcm2835_delay(500);
    return 0;
}


void test_send_syncReq(){

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
      // std::cout<<M.ts23[0];
    } else{
        std::cout<<"Sync failed!";
    }
}

void sendTS_2_3(){

    DataTransport dt(slave_1_Ip, 1695, true);
    // char* tmp_hostname = dt.GetHostname();
    dt.open_connection();
    M.TS3();
    long long unsigned int msgToSend[] = {M.ts23[0], M.ts23[1]};
    dt.send(msgToSend, sizeof(msgToSend));
}

int main(){
    long long t = 10000000;
    long long int ss;
    Test_setPinLow();
    M.keeper.getTime();
    M.keeper.resetTime();
    test_send_syncReq();
    checkForSyncAcpt();
    sendTS_2_3();
    M.TS33();
   while (M.keeper.getTime()<t){}
   Test_setPinHIGH();
    std::cout<<M.ts23[0]<<std::endl;
    std::cout<<M.ts23[1]<<std::endl;
    std::cout<<M.ts23[2]<<std::endl;
    return 0;
}