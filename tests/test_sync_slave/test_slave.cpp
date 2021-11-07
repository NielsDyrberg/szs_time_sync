//
// Created by Martin on 03-11-2021.
//

#include <iostream>
#include <chrono>
#include "timeKeeper.h"
#include "syncMaster.h"
#include "syncSlave.h"
#include "dataTransport.h"
#include <thread>
#include <bcm2835.h>
#define PIN RPI_V2_GPIO_P1_40 //gpio 17
DataTransport dt;
TimeKeeper T;
Slave S;

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
    } else{
        std::cout<<"Sync failed!";
    }
}



void send_syncReq(){

    char MASTER[] = "192.168.0.102";
    DataTransport dt(MASTER, PORT, true);
    // char* tmp_hostname = dt.GetHostname();
    dt.open_connection();
    uint8_t msgToSend[] = {1};
    dt.send(msgToSend, sizeof(msgToSend));
}

void recv_TS23FromMaster(){
    long long unsigned int* bufPTR = nullptr;
    uint8_t size = 0;
    if(dt.receive() > 0) {
        S.TS4();
        bufPTR = dt.GetBuffer(bufPTR, &size);
        for (int i = 0; i < size; i++) {
            S.ts1234[1]= *bufPTR;
        }
        bufPTR++;
        for (int i = 0; i < size; i++) {
            S.ts1234[2]= *bufPTR;
        }
    }

}


int main(){
    long long int ss;
    long long t = 10000000;
    long long int offset;
    long long int RTT;
    long long adj;
    Test_setPinLow();
    S.keeperS.getTime();
    S.keeperS.resetTime();
    checkForSync();
    send_syncReq();
    S.TS44();
   recv_TS23FromMaster();
   offset = S.clockOffset();
    RTT = S.roundTripTime();
   adj = S.adjustClock(offset);
    while (S.adjustClock(offset)<t){}
    Test_setPinHIGH();
   std::cout<<adj<<" adjusted slave clock"<<std::endl;
    std::cout<<RTT<<" RTT"<<std::endl;
   //S.print();

    std::cout << S.ts1234[0]<<std::endl<< S.ts1234[4]<<std::endl<<std::endl <<S.ts1234[1]<<std::endl << S.ts1234[2]<<std::endl << S.ts1234[3]<<std::endl << std::endl;

   //S.TS23Recived();
    return 0;
}