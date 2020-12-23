#ifndef GAMEINFOENTITY_HPP
#define GAMEINFOENTITY_HPP

#include "hwlib.hpp"
#include "rtos.hpp"


struct info{unsigned int plrID; unsigned int data;};

class gameInfoEntity{

private:
    int time;
    info player;
    rtos::pool <int> currentinfoPool;

public:
    gameInfoEntity();

    void setPlrID(unsigned int PlrID);

    void setWpnPwr(unsigned int WpnPwr);

    void setGameTime(unsigned int speeltijd);

    unsigned int getPlrID();

    unsigned int getWpnPwr();

    unsigned int getGameTime();
};

#endif 