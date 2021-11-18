//
// Created by Martin on 10-11-2021.
//

#include <iostream>
//#include <bcm2835.h>
#include "timeKeeper.h"
#include "syncSlave.h"
#define PIN1 RPI_V2_GPIO_P1_40 // Define output pin

int test_timer(){
    long long int adjtime;
    long long int savetime = 0;
    int length = 8;
    int j = 0;
    int o = 1;
    long long int RTT[length];
    //-------------------------------------------------//
    long long int delay = 100000;

   // if(!bcm2835_init())return 1;
    //bcm2835_gpio_fsel(PIN1, BCM2835_GPIO_FSEL_OUTP);
  //  bcm2835_gpio_write(PIN1, LOW);
    //-------------------------------------------------//
    Sync_Slave S;
   // S.keeperS.getTime();
    S.Reset_Time();
    for (int i = 0; (i<length); i++ ) {
        jump :

        S.Sync_Check_And_Accept();
        S.Recive_TS23();
        if (!S.Check_Sync_OK()){
            goto jump;
        }
        adjtime = S.clockOffset();
        //-------------------------------------------------//
        while (S.adjustClock(adjtime) < delay+savetime) {}
      //  bcm2835_gpio_write(PIN1, HIGH);
      //  delayMicroseconds(500);
       // bcm2835_gpio_write(PIN1, LOW);
        savetime = S.adjustClock(adjtime);
       RTT[j] = S.roundTripTime();
       j++;
        //-------------------------------------------------//
    }
    for (int k = 0; (k<length); k++ ) {
        std::cout<<o<<": "<<RTT[k]<<std::endl;
        o++;
    }
   // S.print();
    return 0;
}



int main(){


test_timer();

    return 0;
}