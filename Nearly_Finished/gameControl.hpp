#ifndef GAMECONTROL_HPP
#define GAMECONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "ir_Encoder.hpp"
#include "OLED.hpp"

struct infoGame{unsigned int plrID; unsigned int data;};

class parameterControl;
class gameControl : public rtos::task<>{

enum state_t{idle, running};

private:
    state_t state = idle; 

    rtos::flag flag_StartSignal;
    rtos::flag flag_HitSignal; // pool is optioneel 
    rtos::flag flag_DeathSignal;
    rtos::timer timer_Game;
    
    int hp;

    ir_Encoder &my_Encoder;
    OLED &screen;
    
    void main();

public:
    infoGame gameTime;
    infoGame playerOut;
    infoGame playerIn;
    
    gameControl(ir_Encoder &my_Encoder, OLED &screen);

    void sendParameters(unsigned int plrID, unsigned int data);

    void sendMessage(unsigned int plrID, unsigned int data);

    void calculateHP();

    void startGame();

};

#endif