#include "hwlib.hpp"
#include "rtos.hpp"
#include "gameControl.hpp"

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

public:
    void sendMessage(unsigned int plrID, unsigned int data){
        if(data == 0)
            gameControl.start();
        else 
            gameTime x{plrID, data};
    }

    void getInfo(bool type){
        if(type == 1)
            gameControl.sendParameters(x.plrID, x.data);  // Send game_Time
        else 
            gameControl.sendParameters(keypad());         // Send playerInfo
    }
};