#include "hwlib.hpp"
#include "rtos.hpp"
#include "parameterControl.hpp"
#include "ir_Encoder.hpp"

#ifndef GAMECONTROL_HPP
#define GAMECONTROL_HPP

struct info{unsigned int plrID; unsigned int data;};

class gameControl : public rtos::task<>{

enum state_t{idle, running};

hwlib::target::pin_in_out trigger = hwlib::target::pin_in_out(hwlib::target::pins::d34);

private:
    rtos::flag flag_StartSignal;
    rtos::flag flag_HitSignal; // pool is optioneel 
    rtos::flag flag_DeathSignal;
    rtos::timer timer_Game;
    
    int hp;

    parameterControl &paramCtrl;
    ir_Encoder &my_Encoder;

public:
    gameControl():
        task(4, "ir_Decode"),
        flag_StartSignal(this, "flag_StartSignal"),
        flag_HitSignal(this, "flag_HitSignal"),
        flag_DeathSignal(this, "flag_DeathSignal"),
        timer_Game(this, "timer_Game"),
        hp(100),
        paramCtrl(paramCtrl),
        my_Encoder(my_Encoder) 
    {}

    void triggerPressed(unsigned int plrID, unsigned int data){ //schiet en stuurt naar encoder om te encoden.
        info shooter;
        if( !trigger.read() ){
            my_Encoder.sendMessage(shooter.plrID, shooter.data);
            flagTrigger.set()
        }
    }

    void getEntity(bool type){
        if(type == 1){                  //get entity game_Time 
            paramCtrl.getInfo(1);
        else                            //get entity player_Info 
            paramCtrl.getInfo(0);
    }

    void sendParameters(unsigned int plrID, unsigned int data){
        if(plrID == 0)                  //je hebt de GameTime ontvangen
            info gameTime{plrID, data};
        else                            //je hebt de playerOutput informatie ontvangen
            info playerOut{plrID, data};
    }

    void sendMessage(unsigned int plrID, unsigned int data){ //Wordt gehit door decoder en slaat gegevens op en set flag.
        info playerIn{plrID, data};
        flag_HitSignal.set();
    }

    void calculateHP(){
        hp -= playerIn.data;
        if(hp <= 0){
            flag_DeathSignal.set();
            hp = 100;
        }
    }

    void startGame(){
        flag_StartSignal.set();
    }

}

private:
    void main(){
        for(;;){
            switch(state){
                case idle: {
                    auto event = wait(flag_StartSignal);
                    if(event == flag_StartSignal){
                        getEntity(1);   //get entity game_Time 
                        getEntity(0);   //get entity player_Info
                        state = running; 
                        break;
                    }
                } 
                case running: {
                    timer_Game.set( gameTime.data * 60'000'000 );
                    auto event = wait(flag_HitSignal, flag_DeathSignal, timer_Game);
                    
                    if(event == flag_HitSignal)
                        calculateHP();     
                    else if(event == flag_DeathSignal || event == timer_Game){ // "Game_Over"
                        state = idle;
                        break;
                    }
                    else
                        continue;
                }   
                default:break;        
            }
        }
    }    
};

#endif