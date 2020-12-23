#include "parameterControl.hpp"

parameterControl::parameterControl(gameControl &gameCtrl, gameInfoEntity &gameEntity):
    task(1, "parameterControl"),
    gameCtrl(gameCtrl),
    gameEntity(gameEntity)  
{}

void parameterControl::sendMessage(unsigned int data){
    if(data == 0){
        gameCtrl.startGame();
    }

    else{
        gameEntity.setGameTime(data);
    }
}

void parameterControl::setPlayerInfo(unsigned int plrID, unsigned int data){
    gameEntity.setPlrID(plrID);
    gameEntity.setWpnPwr(data);
}

void parameterControl::main(){
    // for(;;){
    //     switch (state){
    //         case WAIT_for_playerInfo: {
    //             auto event = wait(currentInfoChannel);
    //             if(event == currentInfoChannel){

    //             }
    //         }
    //         case WAIT_for_Gametime: {

    //         }
    //         case WAIT_for_Start: {

    //         }
    //     }      
    // }
}