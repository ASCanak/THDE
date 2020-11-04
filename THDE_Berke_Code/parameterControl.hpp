#include "hwlib.hpp"
#include "rtos.hpp"
#include "KeypadTaak.hpp"
#include "gameControl.hpp"

#ifndef PARAMETERCONTROL_HPP
#define PARAMETERCONTROL_HPP

struct info{unsigned int plrID; unsigned int data;};

class parameterControl : public rtos::<task>{

enum state_t{WAIT, register_plrID, register_wpnpwr, WAIT_for_Gametime, WAIT_for_Start};

private:
    rtos::channel<unsigned int> currentInfoChannel;
    gameControl &gameCtrl;

public:
    info gameTime;
    info currentInfo;

    parameterControl():
        task(3, "parameterControl"),
        currentInfoChannel("currentInfoChannel"),
        gameCtrl(gameCtrl)  
    {}

    void sendMessage(unsigned int plrID, unsigned int data){
        if(data == 0)
            gameCtrl.startGame();
        else 
            gameTime.plrID = plrID;
            gameTime.data = data;
    }

    void setplayerInfo(unsigned int plrID, unsigned int data){
        currentInfo.plrID = plrID;
        currentInfo.data = data;
        currentInfoChannel.write(currentInfo);
    }

    void getInfo(bool type){
        if(type == 1)
            gameCtrl.sendParameters(gameTime.plrID, gameTime.data);  // Send game_Time
        else 
            gameCtrl.sendParameters(currentInfo.plrID, currentInfo.data);  // Send playerInfo
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