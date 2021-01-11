#ifndef GAMECONTROL_HPP
#define GAMECONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "ir_Encoder.hpp"
#include "OLED.hpp"
#include "gameInfoEntity.hpp"

struct infoGame{unsigned int plrID; unsigned int data;};

class gameControl : public rtos::task<>{

enum state_t{idle, running};

private:
    state_t state = idle; 

    rtos::flag flag_StartSignal;
    rtos::flag flag_HitSignal; // pool is optioneel 
    rtos::flag flag_DeathSignal;
    rtos::flag flag_Trigger;
    rtos::timer timer_Game;
    rtos::clock clock_Game;
    
    int hp, timer_Regulation;

    ir_Encoder &my_Encoder;
    OLED &screen;
    gameInfoEntity &game_Entity;
    
    void main();

public:
    int gameTime = 0;
    int seconds = 0;
    infoGame playerOut;
    infoGame playerIn;
    
    gameControl(ir_Encoder &my_Encoder, OLED &screen, gameInfoEntity &game_Entity);

    void sendMessage(unsigned int plrID, unsigned int data);

    void set_triggerFlag();

    unsigned int cooldown();

    void calculateHP();

    void calculateTime();

    void startGame();

};

#endif