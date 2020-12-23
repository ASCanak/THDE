#include "gameInfoEntity.hpp"

gameInfoEntity::gameInfoEntity():
    currentinfoPool("currentinfoPool")
    {}

void gameInfoEntity::setPlrID(unsigned int plrID){
    currentinfoPool.write(plrID);
    player.plrID = currentinfoPool.read();
}

void gameInfoEntity::setWpnPwr(unsigned int wpnPwr){
    currentinfoPool.write(wpnPwr);
    player.data = currentinfoPool.read();
}

void gameInfoEntity::setGameTime(unsigned int speeltijd){
    currentinfoPool.write(speeltijd);
    time = currentinfoPool.read();
}

unsigned int gameInfoEntity::getPlrID(){
    return player.plrID;
}

unsigned int gameInfoEntity::getWpnPwr(){
    return player.data;
}

unsigned int gameInfoEntity::getGameTime(){
    return time;
}