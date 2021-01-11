#include "OLED.hpp"

OLED::OLED(hwlib::target::pin_oc &scl, hwlib::target::pin_oc &sda):
    task(5, "OLED"),
    scl(scl), sda(sda),
    i2c_bus(scl, sda), 
    oled(i2c_bus, 0x3c),
    w1(oled, hwlib::xy(0, 0), hwlib::xy(128, 24)),
    w2(oled, hwlib::xy(0, 24), hwlib::xy(128, 48)),
    scherm(w1, f1), 
    scherm2(w2, f1), 
    eventPool("eventPool"), eventFlag(this, "eventFlag"), 
    plrIDPool("plrIDPool"), plrIDFlag(this, "plrIDFlag"), 
    wpnPwrPool("wpnPwrPool"), wpnPwrFlag(this, "wpnPwrFlag"), 
    minPool("timePool"), minFlag(this, "timeFlag"),
    secPool("timePool"), secFlag(this, "timeFlag"),
    min(0), seconds(0),
    plrID(32), wpnPwr(32)
{}

void OLED::write_eventInfo(unsigned int plrID, unsigned int data, unsigned int hp, unsigned int messageID){
    eventInfo x{plrID, data, hp, messageID};
    eventPool.write(x); eventFlag.set();
}

void OLED::write_Min(unsigned int updated_Time){
    minPool.write(updated_Time); minFlag.set();
}

void OLED::write_Sec(unsigned int updated_Time){
    secPool.write(updated_Time); secFlag.set();
}

void OLED::write_plrID(unsigned int plrID){
    plrIDPool.write(plrID); plrIDFlag.set();
}

void OLED::write_wpnPwrID(unsigned int data){
    wpnPwrPool.write(data); wpnPwrFlag.set();
}

void OLED::write_info_to_OLED(unsigned int myHP, unsigned int min, unsigned int seconds, unsigned int myplrID, unsigned int mywpnPwr){
    scherm2 << "\f";
    scherm2 << "HP     = " << myHP    << "\nTime   = " << min << ":" << seconds <<"\n";
    scherm2<< "plrID  = " << myplrID << "\nwpnPwr = " << mywpnPwr << "\n";
    oled.flush();
}

void OLED::write_event_to_OLED(unsigned int enemyID, unsigned int enemywpnPwr, unsigned int messageID){
    if(messageID == 1)
        scherm << "\f" << "Ready for Setup";
    else if(messageID == 2)
        scherm << "\f" << "Game Started";
    else if(messageID == 3)
        scherm << "\f" << enemywpnPwr << " DMG by "<< enemyID;
    else if(messageID == 4)
        scherm << "\f" << "Game Over\nDeath by Timer";
    else if(messageID == 5)
        scherm << "\f" << "Game Over\nDeath by plr " << enemyID ;
    oled.flush();
}

void OLED::main(){
    hwlib::cout << "OLED\n";
    eventInfo x{32, 32, 100, 1};
    eventPool.write(x);
    write_event_to_OLED(x.plrID, x.data, x.messageID);
    write_info_to_OLED(x.hp, min, seconds, plrID, wpnPwr);
    for(;;){
        auto event = wait(eventFlag + minFlag + secFlag + plrIDFlag + wpnPwrFlag);
        if(event == eventFlag){
            eventInfo x{eventPool.read()};
            write_event_to_OLED(x.plrID, x.data, x.messageID);
        }
        if(event == eventFlag || event == minFlag || event == secFlag || event == plrIDFlag || event == wpnPwrFlag){
            eventInfo x{eventPool.read()};
            min = minPool.read();
            seconds = secPool.read();
            plrID = plrIDPool.read();
            wpnPwr = wpnPwrPool.read();
            write_info_to_OLED(x.hp, min, seconds, plrID, wpnPwr);
        }
    } 
}