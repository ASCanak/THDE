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

    void set_plrID(unsigned int plrID);

    void set_wpnPwr(unsigned int wpnPwr);

    void set_gameTime(unsigned int gameTime);

    unsigned int get_plrID();

    unsigned int get_wpnPwr();

    unsigned int get_gameTime();
};

#endif 