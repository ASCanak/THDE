#ifndef GAMECONTROL_HPP
#define GAMECONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "ir_Encoder.hpp"
#include "OLED.hpp"
#include "trigger.hpp"
#include "gameInfoEntity.hpp"

struct infoGame{unsigned int plrID; unsigned int data;};

class gameControl : public rtos::task<>{

enum state_t{idle, running};

private:
    state_t state = idle; 

    rtos::flag flag_StartSignal;
    rtos::flag flag_HitSignal; // pool is optioneel 
    rtos::flag flag_DeathSignal;
    rtos::timer timer_Game;
    
    int hp, timer_Regulation;

    ir_Encoder &my_Encoder;
    OLED &screen;
    trigger &gun_Trigger;
    gameInfoEntity &game_Entity;
    
    void main();

public:
    int gameTime;
    infoGame playerOut;
    infoGame playerIn;
    
    gameControl(ir_Encoder &my_Encoder, OLED &screen, trigger &gun_Trigger, gameInfoEntity &game_Entity);

    void sendMessage(unsigned int plrID, unsigned int data);

    void calculateHP();

    void startGame();

};

#endif