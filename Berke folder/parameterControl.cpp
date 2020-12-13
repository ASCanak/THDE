#include "parameterControl.hpp"

    parameterControl::parameterControl(gameControl &gameCtrl):
        task(3, "parameterControl"),
        gameCtrl(gameCtrl)  
    {}

    void parameterControl::sendMessage(unsigned int data){
        if(data == 0){
            gameCtrl.startGame();
        }

        else{
            gameEntity.setGametime(data);
        }
    }

    void parameterControl::setplayerInfo(unsigned int plrID, unsigned int data){
        gameEntity.setplrID(plrID);
        gameEntity.setwpnPwr(data);
    }