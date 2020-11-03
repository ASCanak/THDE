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
    rtos::pool<unsigned int> poolCurrentInfo;
    rtos::flag flag_CurrentInfo;

    gameControl &gameCtrl;

public:
    parameterControl():
        task(3, "parameterControl"),
        gameCtrl(gameCtrl)  
    {}

    void sendMessage(unsigned int plrID, unsigned int data){
        if(data == 0)
            gameCtrl.start();
        else 
            gameTime x{plrID, data};
    }

    void getInfo(bool type){
        if(type == 1)
            gameCtrl.sendParameters(x.plrID, x.data);  // Send game_Time
        else 
            gameCtrl.sendParameters(keypad());         // Send playerInfo
    }

    void sendKeyPress(unsigned int plrID, unsigned int data){
        playerInfo currentInfo{plrID, data}
        poolCurrentInfo.write(currentInfo)
        flag_CurrentInfo.set()
    }
private:
    void main( void ){
        for(;;){
            wait(keyPressed(KeypadTaak())
        }
    }
};

#endif