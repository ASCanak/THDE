#ifndef GAMECONTROL_HPP
#define GAMECONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "parameterControl.hpp"
#include "ir_Encoder.hpp"
#include "OLED.hpp"

struct infoGame{unsigned int plrID; unsigned int data;};

hwlib::target::pin_in_out trigger = hwlib::target::pin_in_out(hwlib::target::pins::d34);

class parameterControl;
class gameControl : public rtos::task<>{

enum state_t{idle, running};

private:
    rtos::flag flag_StartSignal;
    rtos::flag flag_HitSignal; // pool is optioneel 
    rtos::flag flag_DeathSignal;
    rtos::timer timer_Game;
    
    int hp;

    parameterControl &paramCtrl;
    ir_Encoder &my_Encoder;
    OLED &screen;
    
    void main();

public:
    infoGame gameTime;
    infoGame playerOut;
    infoGame playerIn;
    
    gameControl(parameterControl &paramCtrl, ir_Encoder &my_Encoder, OLED &screen);

    void getEntity(bool type);

    void sendParameters(unsigned int plrID, unsigned int data);

    void sendMessage(unsigned int plrID, unsigned int data);

    void calculateHP();

    void startGame();

};

#endif