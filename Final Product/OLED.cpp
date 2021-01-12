#include "OLED.hpp"

OLED::OLED(hwlib::target::pin_oc &scl, hwlib::target::pin_oc &sda):
    task(4, "OLED"),
    scl(scl), sda(sda),
    i2c_bus(scl, sda), 
    oled(i2c_bus, 0x3c),
    w1(oled, hwlib::xy(0, 0), hwlib::xy(128, 32)),
    w2(oled, hwlib::xy(0, 32), hwlib::xy(128, 32)),
    scherm(w1, f1), 
    scherm2(w2, f1), 
    hitPool("hitPool"), hitFlag(this, "hitFlag"),
    messagePool("messagePool"), messageFlag(this, "messageFlag"),  
    plrIDPool("plrIDPool"), plrIDFlag(this, "plrIDFlag"), 
    wpnPwrPool("wpnPwrPool"), wpnPwrFlag(this, "wpnPwrFlag"), 
    minPool("timePool"), minFlag(this, "timeFlag"),
    secPool("timePool"), secFlag(this, "timeFlag")
{}

void OLED::write_hitInfo(unsigned int plrID, unsigned int data, unsigned int hp){
    hitInfo x{plrID, data, hp};
    hitPool.write(x); hitFlag.set();
}

void OLED::write_message(unsigned int messageID, unsigned int number){
    messageInfo y{messageID, number};
    messagePool.write(y); messageFlag.set();
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

void OLED::initialize_OLED(){
    write_message(0, 100);
    write_hitInfo(0, 0, 100);
    write_Min(0);
    write_Sec(0);
    write_plrID(32);
    write_wpnPwrID(32);
}

void OLED::display_HUD(unsigned int myHP, unsigned int min, unsigned int seconds, unsigned int myplrID, unsigned int mywpnPwr){
    scherm2 << "\f";
    scherm2 << "HP     = " << myHP    << "\nTime   = " << min << ":" << seconds <<"\n";
    scherm2 << "plrID  = " << myplrID << "\nwpnPwr = " << mywpnPwr << "\n";
    oled.flush();
}

void OLED::display_Message(unsigned int enemyID, unsigned int enemywpnPwr, unsigned int messageID, unsigned int number){
    if(enemyID != 0 && number == 100)
        scherm << "\f" << enemywpnPwr << " DMG by " << enemyID;
    if(messageID == 0)
        scherm << "\f" << "Initializing...";
    else if(messageID == 1)
        scherm << "\f" << "Game Started";
    else if(messageID == 2)
        scherm << "\f" << "Invalid Input";
    else if(messageID == 3)
        scherm << "\f" << "A for plrID|\nB for wpnPwr|\nC for cmd|";
    else if(messageID == 4)
        scherm << "\f" << "enter plrID:";
    else if(messageID == 5)
        scherm << "\f" << "enter wpnPwr:";
    else if(messageID == 6)
        scherm << "\f" << "enter data:";
    else if(messageID == 7)
        scherm << "\f" << "plrID saved";
    else if(messageID == 8)
        scherm << "\f" << "wpnPwrID saved";
    else if(messageID == 9)
        scherm << "\f" << "time saved";
    // else if(messageID == 10)
    //     scherm << "\f" << "enter 2nd digit or press \n* to save current digit:";              
    else if(messageID == 11)
        scherm << "\f" << "Game Over\nDeath by Timer";
    else if(messageID == 12)
        scherm << "\f" << "Game Over\nDeath by plr ";
    if(enemyID == 0 && enemywpnPwr == 0 && number != 100)
        scherm << number;
    oled.flush();
}

void OLED::main(){
    hwlib::cout << "OLED\n";
    initialize_OLED();
    for(;;){
        auto event = wait(hitFlag + messageFlag + minFlag + secFlag + plrIDFlag + wpnPwrFlag);
        if(event == hitFlag){
            hitInfo x{hitPool.read()};
            display_Message(x.plrID, x.data, 100, 100);
        }
        else if(event == messageFlag){
            messageInfo y{messagePool.read()};
            display_Message(0, 0, y.message, y.number);
        }
        if(event == hitFlag || event == minFlag || event == secFlag || event == plrIDFlag || event == wpnPwrFlag){
            hitInfo x{hitPool.read()};
            display_HUD(x.hp, minPool.read(), secPool.read(), plrIDPool.read(), wpnPwrPool.read());
        }
    } 
}