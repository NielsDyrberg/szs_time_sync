//
// Created by mc on 29-10-2021.
//

#include "../include/syncMaster.h"
#define PORT 1696
#define SyncReq 0xFF // tallet 255 = "1111 1111" for anmodning om sync
#define SyncAcpt 0x01 // tallet   1 = "0000 0001" for accept af sync
#define SyncDecline 0x81 // tallet   129 = "1000 0001" for decline af sync

/**********************************************************************************************************************
 * Static variables
 **********************************************************************************************************************/





Sync_Master::Sync_Master ()= default;


Sync_Master::Sync_Master(char *host, bool is_ip): dt(host, PORT, is_ip, comm_buffer, SYNC_COMM_BUFFER_SIZE),  ts23{0,0}{

}
void Sync_Master::Reset_Time() {
    keeper.resetTime();
}
long long Sync_Master::Get_Time() {
    return keeper.getTime();
}

void Sync_Master::TS2() {
    ts23[0] = keeper.getTime();
    std::cout<<ts23[0]<<std::endl;

}

void Sync_Master::TS3() {
    ts23[1] = keeper.getTime();

}

void Sync_Master::SyncReq_and_accept(){
    uint8_t * bufPTR = nullptr;
    uint16_t size = 0;
    uint8_t msg[] = {SyncReq};
    std::cout<<"Så langt så godt 2.0 :) "<<std::endl;
    if(dt.send_and_receive(msg, sizeof(msg)) > 0 ) {
        std::cout<<"Sender "<<std::endl;
        bufPTR = dt.GetBuffer(bufPTR, &size);
        if (*bufPTR == SyncAcpt){

            TS2();
        }

    } else{
        std::cout<<"Sender ikke  "<<std::endl;
    }
}
void Sync_Master::Send_TS23(){
    TS3();
    long long unsigned int msg[] ={ts23[0], ts23[1]};
    std::cout<<"Sender TS "<<std::endl;
    dt.send(msg, sizeof(msg));


}

bool Sync_Master::Wait_for_Sync_OK(){
    bool check = false;
    long long unsigned int *bufPTR = nullptr;
    uint8_t size = 0;
    if (dt.receive(false) > 0) {
        bufPTR = dt.GetBuffer(bufPTR, &size);
        if (*bufPTR == SyncAcpt) {
            check = true;
        }
    }
    return check ;
}



