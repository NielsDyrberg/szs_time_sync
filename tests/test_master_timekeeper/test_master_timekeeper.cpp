//
// Created by Martin on 10-11-2021.
//

#include <iostream>
#include <unistd.h>
#include "timeKeeper.h"
#include "syncMaster.h"
#include <bcm2835.h>
#define PIN  RPI_V2_GPIO_P1_40 // Define output pin




int main(){
    //-------------------------------------------------//
    long long int delay = 2000000;
    long long int savetime =0;
    if(!bcm2835_init())return 1;
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(PIN, LOW);

    //-------------------------------------------------//
    TimeKeeper_Master M;
    M.keeper.resetTime();
    for (int i = 0; (i<7); i++ ){

    M.SyncReq_and_accept();
    M.Send_TS23();
    //-------------------------------------------------//
    while(M.keeper.getTime()<delay+savetime){}
    bcm2835_gpio_write(PIN, HIGH);
    sleep(1);
    bcm2835_gpio_write(PIN, LOW);
    savetime = M.keeper.getTime();

    }

    //-------------------------------------------------//

    return 0;
}