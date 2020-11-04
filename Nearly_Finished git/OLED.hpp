#ifndef OLED_HPP
#define OLED_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

struct hitInfo {unsigned int plrID; unsigned int data; unsigned int hp;};




class OLED : public rtos::task<>{

private:

    rtos::pool<hitInfo> hitPool; rtos::flag hitFlag;
    rtos::pool<unsigned int> plrIDPool; rtos::flag plrIDFlag;
    rtos::pool<unsigned int> wpnPwrPool; rtos::flag wpnPwrFlag;
    rtos::pool<unsigned int> timePool; rtos::flag timeFlag;

    unsigned int time;
    unsigned int plrID;
    unsigned int wpnPwr;  

    hwlib::target::pin_oc& scl;
    hwlib::target::pin_oc& sda;
    hwlib::i2c_bus_bit_banged_scl_sda i2c_bus;
    hwlib::glcd_oled oled;
    hwlib::font_default_8x8 f1;

    hwlib::window_part_t w1;
    hwlib::terminal_from scherm;

public:
    OLED(hwlib::target::pin_oc& scl, hwlib::target::pin_oc& sda): 
        task(5, "OLED"),
        hitPool("hitPool"), hitFlag(this, "hitFlag"), 
        plrIDPool("plrIDPool"), plrIDFlag(this, "plrIDFlag"), 
        wpnPwrPool("wpnPwrPool"), wpnPwrFlag(this, "wpnPwrFlag"), 
        timePool("timePool"), timeFlag(this, "timeFlag"),
        time(60),
        plrID(1),
        wpnPwr(0),
        scl(scl),
        sda(sda),
        i2c_bus(scl, sda),
        oled(i2c_bus, 0x3c),
        w1(oled, hwlib::xy(0, 0), hwlib::xy(128, 32)),
        scherm(w1,f1)
    {}

    void write_HitInfo(unsigned int plrID, unsigned int data, unsigned int hp){
        hitInfo x{plrID, data, hp};
        hitPool.write(x); hitFlag.set();
    }
    void write_Time(unsigned int time){
         timePool.write(time); timeFlag.set();
    }
    void write_plrID(unsigned int plrID){
        plrIDPool.write(plrID); plrIDFlag.set();
    }
    void write_wpnPwrID(unsigned int data){
        wpnPwrPool.write(data); wpnPwrFlag.set();
    }
    void write_to_Oled(unsigned int EnemyID, unsigned int EnemywpnPwr, unsigned int myHP, unsigned int time, unsigned int myplrID, unsigned int mywpnPwr){
        scherm << "\t0001" << "Hit By: " << EnemyID << " For " << EnemywpnPwr << " Damage "<< "\n";
        scherm << "\t0010" << myHP <<"\n";
        scherm << "\t0015" << time <<"\n";
        scherm << "\t0020" << myplrID <<"\n";
        scherm << "\t0025" << mywpnPwr <<"\n";
        scherm.hwlib::ostream::flush();
    }

private:
    void main(){
        for(;;){
            auto event = wait(hitFlag + timeFlag + plrIDFlag + wpnPwrFlag);
            if(event == hitFlag || event == timeFlag || event == plrIDFlag || event == wpnPwrFlag){
                hitInfo x{hitPool.read()};
                time = timePool.read();
                plrID = plrIDPool.read();
                wpnPwr = wpnPwrPool.read();
                write_to_Oled(x.plrID, x.data, x.hp, time, plrID, wpnPwr);
            }
        } 
    }
};

#endif