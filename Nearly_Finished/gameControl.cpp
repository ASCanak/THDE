#include "hwlib.hpp"
#include "rtos.hpp"
#include "parameterControl.hpp"
#include "ir_Encoder.hpp"
#include "OLED.hpp"
#include "gameControl.hpp"

    void gameControl::main(){
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
                    auto event = wait(flag_HitSignal + flag_DeathSignal + timer_Game);
                    
                    if(event == flag_HitSignal){
                        calculateHP();
                        screen.write_HitInfo(playerIn.plrID, playerIn.data, hp);
                    }
                    else if(event == flag_DeathSignal || event == timer_Game){ // "Game_Over"
                        hwlib::cout << "this nigga died, idiot kid i told you he was lamps" << endl;
                        screen.write_HitInfo(playerIn.plrID, playerIn.data, 0);
                        state = idle;
                        break;
                    }
                    else if(!trigger.read()){
                        my_Encoder.sendMessage(playerOut.plrID, playerOut.data);
                    }
                    else
                        continue;
                }   
                default:break;        
            }
        }
    }

    gameControl(parameterControl &paramCtrl, ir_Encoder &my_Encoder, OLED &screen):
        task(4, "gameControl"),
        flag_StartSignal(this, "flag_StartSignal"),
        flag_HitSignal(this, "flag_HitSignal"),
        flag_DeathSignal(this, "flag_DeathSignal"),
        timer_Game(this, "timer_Game"),
        hp(100),
        paramCtrl(paramCtrl),
        my_Encoder(my_Encoder),
        screen(screen) 
    {}

    void gameControl::getEntity(bool type){
        if(type == 1){                  //get entity game_Time 
            paramCtrl.getInfo(1);
        else                            //get entity player_Info 
            paramCtrl.getInfo(0);
    }

    void gameControl::sendParameters(unsigned int plrID, unsigned int data){
        if(plrID == 0){                  //je hebt de GameTime ontvangen
            gameTime.plrID = plrID;
            gameTime.data = data;
        }
        else{                            //je hebt de playerOutput informatie ontvangen
            playerOut.plrID = plrID;
            playerOut.data = data;
        }
    }

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

}

    