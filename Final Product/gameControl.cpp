#include "gameControl.hpp"

    void gameControl::main(){
        for(;;){
            switch(state){
                case idle: {
                    auto event = wait(flag_StartSignal);
                    if(event == flag_StartSignal){
                        playerOut.plrID = game_Entity.getPlrID();
                        playerOut.data = game_Entity.getWpnPwr();
                        gameTime = game_Entity.getGameTime(); 
                        state = running;
                        break;
                    }
                } 
                case running: {
                    if(timer_Regulation == 0){
                        timer_Game.set( gameTime * 60'000'000 );
                        timer_Regulation++;
                    }
                    auto event = wait(flag_HitSignal + flag_DeathSignal + timer_Game);
                    
                    if(event == flag_HitSignal){
                        calculateHP();
                        screen.write_HitInfo(playerIn.plrID, playerIn.data, hp);
                    }
                    else if(event == flag_DeathSignal || event == timer_Game){ // "Game_Over"
                        hwlib::cout << "this boi died, idiot kid i told you he was lamps \n";
                        screen.write_HitInfo(playerIn.plrID, playerIn.data, 0);
                        state = idle;
                        timer_Regulation = 0;
                        break;
                    }
                    else if(!(gun_Trigger.triggerRead())){
                        my_Encoder.sendMessage(playerOut.plrID, playerOut.data);
                    }
                    else
                        continue;
                }   
                default:break;        
            }
        }
    }

    gameControl::gameControl(ir_Encoder &my_Encoder, OLED &screen, trigger &gun_Trigger, gameInfoEntity &game_Entity):
        task(0, "gameControl"),
        flag_StartSignal(this, "flag_StartSignal"),
        flag_HitSignal(this, "flag_HitSignal"),
        flag_DeathSignal(this, "flag_DeathSignal"),
        timer_Game(this, "timer_Game"),
        hp(100), timer_Regulation(0),
        my_Encoder(my_Encoder),
        screen(screen),
        gun_Trigger(gun_Trigger),
        game_Entity(game_Entity) 
    {}

    void gameControl::sendMessage(unsigned int plrID, unsigned int data){ //Wordt gehit door decoder, slaat gegevens op en set flag.
        playerIn.plrID = plrID;
        playerIn.data = data;
        flag_HitSignal.set();
    }

    void gameControl::calculateHP(){
        hp -= playerIn.data;
        if(hp <= 0){
            flag_DeathSignal.set();
            hp = 100;
        }
    }

    void gameControl::startGame(){
        flag_StartSignal.set();
    }