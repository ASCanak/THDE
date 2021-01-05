#ifndef PARAMETERCONTROL_HPP
#define PARAMETERCONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "gameControl.hpp"
#include "gameInfoEntity.hpp"

class gameControl;
class parameterControl{

private:
    gameControl &gameCtrl;
    gameInfoEntity &gameEntity;

public:
    parameterControl(gameControl &gameCtrl, gameInfoEntity &gameEntity);

    void sendMessage(unsigned int data);

    void setPlayerInfo(unsigned int plrID, unsigned int data);
};

#endif