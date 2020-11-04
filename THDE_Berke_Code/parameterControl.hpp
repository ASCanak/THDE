#include "hwlib.hpp"
#include "rtos.hpp"
#include "KeypadTaak.hpp"
#include "gameControl.hpp"

#ifndef PARAMETERCONTROL_HPP
#define PARAMETERCONTROL_HPP

struct gameTime{unsigned int plrID; unsigned int data;};
struct playerInfo{unsigned int plrID; unsigned int data;};

class parameterControl : public rtos::<task>{

enum state_t{WAIT, register_plrID, register_wpnpwr, WAIT_for_Gametime, WAIT_for_Start};

private:
    rtos::channel<unsigned int> currentInfoChannel;
    gameControl &gameCtrl;

public:
    parameterControl():
        task(3, "parameterControl"),
        currentInfoChannel("currentInfoChannel"),
        gameCtrl(gameCtrl)  
    {}

    void sendMessage(unsigned int plrID, unsigned int data){
        if(data == 0)
            gameCtrl.startGame();
        else 
            gameTime x{plrID, data};
    }

    void setplayerInfo(unsigned int plrID, unsigned int data){
        playerInfo currentInfo{plrID, data};
        currentInfoChannel.write(currentInfo);
    }

    void getInfo(bool type){
        gameTime x;
        playerInfo CurrentInfo;
        if(type == 1)
            gameCtrl.sendParameters(x.plrID, x.data);  // Send game_Time
        else 
            gameCtrl.sendParameters(CurrentInfo.plrID, CurrentInfo.data);  // Send playerInfo
    }

private:
    void main(){
        for(;;){
            switch (state){
                case WAIT: {
                    
                }
            }
            
    }
};

#endif