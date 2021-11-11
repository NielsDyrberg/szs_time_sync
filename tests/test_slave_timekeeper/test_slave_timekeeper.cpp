//
// Created by Martin on 10-11-2021.
//

#include <iostream>
#include <bcm2835.h>
#include "timeKeeper.h"
#include "syncSlave.h"
#define PIN1 RPI_V2_GPIO_P1_40 // Define output pin

int test_timer(){
    long long int adjtime;
    long long int savetime = 0;
    //-------------------------------------------------//
    long long int delay = 2000000;

    if(!bcm2835_init())return 1;
    bcm2835_gpio_fsel(PIN1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(PIN1, LOW);
    //-------------------------------------------------//
    Timekeeper_Slave S;
    S.keeperS.resetTime();
    for (int i = 0; (i<7); i++ ) {
        S.Sync_Check_And_Accept();
        S.Recive_TS23();
        adjtime = S.clockOffset();
        //-------------------------------------------------//
        while (S.adjustClock(adjtime) < delay+savetime) {}
        bcm2835_gpio_write(PIN1, HIGH);
        sleep(1);
        bcm2835_gpio_write(PIN1, LOW);
        savetime = S.adjustClock(adjtime);
        //-------------------------------------------------//
    }
    S.print();
    return 0;
}



int main(){

test_timer();

    return 0;
}