#include "hwlib.hpp"
#include "rtos.hpp"
#include "gameControl.hpp"

#ifndef PARAMETERCONTROL_HPP
#define PARAMETERCONTROL_HPP

struct gameTime{unsigned int plrID; unsigned int data;};

class parameterControl : public rtos::<task>{

enum state_t{WAIT, register_plrID, register_wpnpwr, WAIT_for_Gametime, WAIT_for_Start};

enum keyID{key1, key2, key3, keyA, 
           key4, key5, key6, keyB, 
           key7, key8, key9, keyC, 
           keySter, key0, keyHash, keyD};

private:
    // rtos::channel<bool> keyChannel;
    // rtos::

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
};

#endif