#ifndef PARAMETERCONTROL_HPP
#define PARAMETERCONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "gameControl.hpp"
#include "gameInfoEntity.hpp"

struct infoParam{unsigned int plrID; unsigned int data;};

class gameControl;
class parameterControl : public rtos::task<>{

//enum state_t{register_playerInfo, WAIT_for_Gametime, WAIT_for_Start};

private:
    gameControl &gameCtrl;
    gameInfoEntity &gameEntity;

    void main();

public:
    parameterControl(gameControl &gameCtrl, gameInfoEntity &gameEntity);

    void sendMessage(unsigned int data);

    void setPlayerInfo(unsigned int plrID, unsigned int data);
};

#endif