#include "gameinfoEntity.hpp"

gameinfoEntity::gameinfoEntity():
    currentinfoPool(this, "currentinfoPool")
    {}

void gameinfoEntity::setPlrID(unsigned int plrID){
    currentinfoPool.write(plrID);
    player.plrID = currentInfo.read(plrID);
}

void gameinfoEntity::setWpnPwr(unsigned int wpnPwr){
    currentinfoPool.write(wpnPwr);
    player.data = currentinfoPool.read();
}

void gameinfoEntity::setGametime(unsigned int speeltijd){
    currentinfoPool.write(speeltijd);
    time = currentinfoPool.read();
}

void gameinfoEntity::getwpnPwr(){
    playerOut.data = player.data;
}

void gameinfoEntity::getGametime(){
    gameTime = time;
}