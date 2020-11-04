#include "hwlib.hpp"
#include "rtos.hpp"
#include "gameControl.hpp"
#include "parameterControl.hpp"

    parameterControl::parameterControl(gameControl &gameCtrl):
        task(3, "parameterControl"),
        gameCtrl(gameCtrl)  
    {}

    void parameterControl::sendMessage(unsigned int plrID, unsigned int data){
        if(data == 0){
            gameCtrl.sendParameters(gameTime.plrID, gameTime.data);
            gameCtrl.sendParameters(currentInfo.plrID, currentInfo.data);
            gameCtrl.startGame();
        }
        else{
            gameTime.plrID = plrID;
            gameTime.data = data;
        }
    }

    void parameterControl::setplayerInfo(unsigned int plrID, unsigned int data){
        currentInfo.plrID = plrID;
        currentInfo.data = data;
    }