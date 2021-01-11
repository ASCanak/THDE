#include "parameterControl.hpp"

parameterControl::parameterControl(gameControl &gameCtrl, gameInfoEntity &gameEntity):
    gameCtrl(gameCtrl),
    gameEntity(gameEntity)  
{}

void parameterControl::sendMessage(unsigned int data){
    if(data == 0)
        gameCtrl.startGame();
    else
        gameEntity.set_gameTime(data);
}

void parameterControl::set_plrID(unsigned int plrID){
    gameEntity.set_plrID(plrID);
}

void parameterControl::set_wpnPwr(unsigned int data){
    gameEntity.set_wpnPwr(data);
}