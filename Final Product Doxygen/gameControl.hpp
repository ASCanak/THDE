/// This file contains Doxygen lines
/// \brief
/// gameControl class and gameControl task
/// \details
/// This is a gameControl class that inherits from rtos::task
/// Makes it so that the game can be played

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
    
    /// \brief
    /// Saves data and sets flag
    /// \details
    /// This function when hit, saves data in a struct and sets hit flag
    void sendMessage(unsigned int plrID, unsigned int data);
    
    /// \brief
    /// Sets flag
    /// \details
    /// This function Sets trigger flag
    void set_triggerFlag();
    
    /// \brief
    /// Adds cooldown mechanism
    /// \details
    /// This function returns the cooldown number based on the user's wpnPwr input   
    unsigned int cooldown();
    
    /// \brief
    /// Calculates HP
    /// \details
    /// This function calculates the HP, when HP reaches zero and sets death flag
    void calculateHP();
    
    /// \brief
    /// Calculates time
    /// \details
    /// This function calculates the time whilst writing the current time to the OLED
    void calculateTime();
    
    /// \brief
    /// Starts game
    /// \details
    /// This function sets the start flag
    void startGame();

};

#endif
