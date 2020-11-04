#include "hwlib.hpp"
#include "rtos.hpp"
#include "gameControl.hpp"
#include "parameterControl.hpp"

    parameterControl(gameControl &gameCtrl):
        task(3, "parameterControl"),
        currentInfoChannel("currentInfoChannel"),
        gameCtrl(gameCtrl)  
    {}

    void parameterControl::sendMessage(unsigned int plrID, unsigned int data){
        if(data == 0)
            gameCtrl.startGame();
        else 
            gameTime.plrID = plrID;
            gameTime.data = data;
    }

    void parameterControl::setplayerInfo(unsigned int plrID, unsigned int data){
        currentInfo.plrID = plrID;
        currentInfo.data = data;
    }

    void parameterControl::getInfo(bool type){
        if(type == 1)
            gameCtrl.sendParameters(gameTime.plrID, gameTime.data);  // Send game_Time
        else 
            gameCtrl.sendParameters(currentInfo.plrID, currentInfo.data);  // Send playerInfo
    }