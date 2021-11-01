//
// Created by ncpd on 21-10-2021.
// Freqense 1MHz
// piodtime 1µs, pulsewith 500ns
#include "test_pigpio.h"
#include <pigpio.h>
#include <iostream>
#include <chrono>



#include <thread>



int test_pigio() {


    std::cout << "Nyeste version kører" << std::endl;


    if (gpioInitialise() < 0) exit(1);
    int ticksNow = 0;
    unsigned int readPin = 17;
    unsigned int setPin = 27;
    gpioSetMode(readPin, PI_INPUT);
    gpioSetPullUpDown(readPin, PI_PUD_DOWN);
    gpioSetMode(setPin, PI_OUTPUT);
    gpioWrite(27, 0);
    bool sleep = false;
    auto start = std::chrono::system_clock::now();
    auto slut = std::chrono::system_clock::now();
    auto resul = std::chrono::duration_cast<std::chrono::microseconds>(slut - start);

    while (gpioRead(17) == PI_LOW) {}

    sleep = true;
    start = std::chrono::high_resolution_clock::now();
    while (sleep) {
        slut = std::chrono::high_resolution_clock::now();
        resul = std::chrono::duration_cast<std::chrono::microseconds>(slut - start);
        if (resul.count() > 600000000)


            sleep = false;
    }
    gpioWrite(27, 1);
    std::cout<<resul.count();
    std::cout << "TEST DONE" << std::endl;






return 0;
}




