#include "parameterControl.hpp"

parameterControl::parameterControl(gameControl &gameCtrl, gameInfoEntity &gameEntity):
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