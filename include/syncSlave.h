//
// Created by Martin on 29-10-2021.
//

#ifndef CUSTOM_TIMEKEEPER_SYNCSLAVE_H
#define CUSTOM_TIMEKEEPER_SYNCSLAVE_H
#include "timeKeeper.h"
#include "udp_server.h"


class Sync_Slave {

public:
    Sync_Slave();
    void Reset_Time();
    void TS1();
    void Sync_Check_And_Accept();
    void TS4();
    unsigned int roundTripTime();
    long long clockOffset();
    bool Check_Sync_OK();
    long long adjustClock( long long CO);
    void print();
    void Recive_TS23();
    uint16_t Set_RTT_Filter(uint16_t);

    /**
     * @brief Returns the adjusted current time.
     * @return Adjusted current time.
     */
    long long int Get_Time();

protected:
private:
    TimeKeeper keeperS;
    UDP_server dt;
    long long unsigned ts1234[4];
    uint16_t RTTallowed;





};
















#endif //CUSTOM_TIMEKEEPER_SYNCSLAVE_H
