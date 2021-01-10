#include "gameInfoEntity.hpp"

gameInfoEntity::gameInfoEntity():
    currentinfoPool("currentinfoPool")
    {}

void gameInfoEntity::set_plrID(unsigned int plrID){
    currentinfoPool.write(plrID);
    player.plrID = currentinfoPool.read();
}

void gameInfoEntity::set_wpnPwr(unsigned int wpnPwr){
    currentinfoPool.write(wpnPwr); 
    player.data = currentinfoPool.read();
}

void gameInfoEntity::set_gameTime(unsigned int gameTime){
    currentinfoPool.write(gameTime);
    time = currentinfoPool.read();
}

unsigned int gameInfoEntity::get_plrID(){
    return player.plrID;
}

unsigned int gameInfoEntity::get_wpnPwr(){
    return player.data;
}

unsigned int gameInfoEntity::get_gameTime(){
    return time;
}