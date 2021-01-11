#include "OLED.hpp"

OLED::OLED(hwlib::target::pin_oc &scl, hwlib::target::pin_oc &sda):
    task(5, "OLED"),
    scl(scl), sda(sda),
    i2c_bus(scl, sda), 
    oled(i2c_bus, 0x3c),
    w1(oled, hwlib::xy(0, 0), hwlib::xy(128, 64)),
    scherm(w1, f1),
    hitPool("hitPool"), hitFlag(this, "hitFlag"), 
    plrIDPool("plrIDPool"), plrIDFlag(this, "plrIDFlag"), 
    wpnPwrPool("wpnPwrPool"), wpnPwrFlag(this, "wpnPwrFlag"), 
    minPool("timePool"), minFlag(this, "timeFlag"),
    secPool("timePool"), secFlag(this, "timeFlag"),
    min(0), seconds(0),
    plrID(32), wpnPwr(32)
{}

void OLED::write_HitInfo(unsigned int plrID, unsigned int data, unsigned int hp){
    hitInfo x{plrID, data, hp};
    hitPool.write(x); hitFlag.set();
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

void OLED::write_to_Oled(unsigned int enemyID, unsigned int enemywpnPwr, unsigned int myHP, unsigned int min, unsigned int seconds, unsigned int myplrID, unsigned int mywpnPwr){
    scherm << "\f" << enemywpnPwr << " DMG by "<< enemyID << "\n\n";
    scherm << "HP     = " << myHP    << "\nTime   = " << min << ":" << seconds <<"\n";
    scherm << "plrID  = " << myplrID << "\nwpnPwr = " << mywpnPwr << "\n";
    oled.flush();
}

void OLED::main(){
    hwlib::cout << "OLED\n";
    hitInfo x{32, 32, 100};
    hitPool.write(x);
    write_to_Oled(x.plrID, x.data, x.hp, min, seconds, plrID, wpnPwr);
    for(;;){
        auto event = wait(hitFlag + minFlag + secFlag + plrIDFlag + wpnPwrFlag);
        if(event == hitFlag || event == minFlag || event == secFlag || event == plrIDFlag || event == wpnPwrFlag){
            hitInfo x{hitPool.read()};
            min = minPool.read();
            seconds = secPool.read();
            plrID = plrIDPool.read();
            wpnPwr = wpnPwrPool.read();
            write_to_Oled(x.plrID, x.data, x.hp, min, seconds, plrID, wpnPwr);
        }
    } 
}