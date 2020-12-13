#ifndef GAMEINFOENTITY_HPP
#define GAMEINFOENTITY_HPP

#include "rtos.hpp"
#include "gameControl.hpp"


struct info{unsigned int plrID; unsigned int data;};

class gameinfoEntity{
private:
    int time;
    info player;
    rtos::pool < int > currentinfoPool;
public:
    gameinfoEntity();

    void setplrID(unsigned int PlrID);

    void setwpnPwr(unsigned int WpnPwr);

    void setGametime(unsigned int speeltijd);

    void getwpnPwr();

    void getGametime();

};

#endif 