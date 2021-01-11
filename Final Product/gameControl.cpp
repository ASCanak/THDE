#include "gameControl.hpp"

void gameControl::main(){
    hwlib::cout << "gameControl\n";
    for(;;){
        switch(state){
            case idle: {
                auto event = wait(flag_StartSignal);
                if(event == flag_StartSignal){
                    playerOut.plrID = game_Entity.get_plrID();
                    playerOut.data = game_Entity.get_wpnPwr();
                    gameTime = game_Entity.get_gameTime(); 
                    state = running;
                    break;
                }
            } 
            case running: {
                if(timer_Regulation == 0){
                    timer_Game.set(gameTime * 59'000'000);
                    timer_Regulation++;
                }
                auto event = wait(flag_HitSignal + flag_DeathSignal + flag_Trigger + timer_Game + clock_Game);
                
                if(event == flag_HitSignal){
                    calculateHP();
                    screen.write_eventInfo(playerIn.plrID, (playerIn.data * 2) + 10, hp, 3);
                }
                else if(event == timer_Game){ // "Game_Over, death by timer"
                    hwlib::cout << "this boi died, idiot kid i told you he was lamps \n";
                    hp = 100;
                    screen.write_eventInfo(0, 0, hp, 4);
                    state = idle;
                    timer_Regulation = 0;
                    break;
                }
                else if(event == flag_DeathSignal){ // "Game_Over, death by player"
                    hwlib::cout << "this boi died, idiot kid i told you he was lamps \n";
                    screen.write_eventInfo(playerIn.plrID, (playerIn.data * 2) + 10, hp, 5);
                    state = idle;
                    seconds = 0;
                    timer_Regulation = 0;
                    break;
                }
                else if(event == clock_Game){
                    calculateTime();
                }
                else if(event == flag_Trigger){
                    my_Encoder.sendMessage(playerOut.plrID, playerOut.data);
                }
            }   
            default:break;        
        }
    }
}

gameControl::gameControl(ir_Encoder &my_Encoder, OLED &screen, gameInfoEntity &game_Entity):
    task(3, "gameControl"),
    flag_StartSignal(this, "flag_StartSignal"),
    flag_HitSignal(this, "flag_HitSignal"),
    flag_DeathSignal(this, "flag_DeathSignal"),
    flag_Trigger(this, "flag_Trigger"),
    timer_Game(this, "timer_Game"),
    clock_Game(this, 1000 * rtos::ms, "clock_Game"),
    hp(100), timer_Regulation(0),
    my_Encoder(my_Encoder),
    screen(screen),
    game_Entity(game_Entity) 
{}

void gameControl::sendMessage(unsigned int plrID, unsigned int data){ //Wordt gehit door decoder, slaat gegevens op en set flag.
    playerIn.plrID = plrID;
    playerIn.data = data;
    flag_HitSignal.set();
}

unsigned int gameControl::cooldown(){
    return (playerOut.data * 2 + 60); 
}

void gameControl::calculateHP(){
    hp -= (playerIn.data * 2) + 10;
    if(hp <= 0){
        hp = 100;
        flag_DeathSignal.set();
    }
}

void gameControl::calculateTime(){
    if(seconds == 0){
        gameTime--;
        seconds = 59;
        screen.write_Min(gameTime);
        screen.write_Sec(seconds);
    }
    else{
        seconds--;
        screen.write_Sec(seconds);
    }
}

void gameControl::set_triggerFlag(){
    flag_Trigger.set();
}

void gameControl::startGame(){
    flag_StartSignal.set();
}