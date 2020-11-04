#ifndef PARAMETERCONTROL_HPP
#define PARAMETERCONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "gameControl.hpp"

struct infoParam{unsigned int plrID; unsigned int data;};

class gameControl;
class parameterControl : public rtos::task<>{

// enum state_t{register_playerInfo, WAIT_for_Gametime, WAIT_for_Start};

private:
    gameControl &gameCtrl;

    void main();

public:
    infoParam gameTime;
    infoParam currentInfo;

    parameterControl(gameControl &gameCtrl);

    void sendMessage(unsigned int plrID, unsigned int data);

    void setplayerInfo(unsigned int plrID, unsigned int data);

// private:
//     void main(){
//         for(;;){
//             switch (state){
//                 case WAIT_for_playerInfo: {
//                     auto event = wait(currentInfoChannel);
//                     if(event == currentInfoChannel){
                        
//                     }
//                 }
//                 case WAIT_for_Gametime: {
                    
//                 }
//                 case WAIT_for_Start: {
                    
//                 }
//             }      
//         }
//     }
};

#endif