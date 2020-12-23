#ifndef OLED_HPP
#define OLED_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

struct hitInfo {unsigned int plrID; unsigned int data; unsigned int hp;};

class OLED : public rtos::task<>{

private:
    hwlib::target::pin_oc &scl;
    hwlib::target::pin_oc &sda;

    hwlib::i2c_bus_bit_banged_scl_sda i2c_bus;
    hwlib::glcd_oled oled;
    hwlib::font_default_8x8 f1;

    hwlib::window_part_t w1;
    hwlib::terminal_from scherm;
    
    rtos::pool<hitInfo> hitPool; rtos::flag hitFlag;
    rtos::pool<unsigned int> plrIDPool; rtos::flag plrIDFlag;
    rtos::pool<unsigned int> wpnPwrPool; rtos::flag wpnPwrFlag;
    rtos::pool<unsigned int> timePool; rtos::flag timeFlag; 

    unsigned int time, plrID, wpnPwr;

    void main();
    
public:
    OLED(hwlib::target::pin_oc &scl, hwlib::target::pin_oc &sda);
    void write_HitInfo(unsigned int plrID, unsigned int data, unsigned int hp);
    void write_Time(unsigned int time);
    void write_plrID(unsigned int plrID);
    void write_wpnPwrID(unsigned int data);
    void write_to_Oled(unsigned int EnemyID, unsigned int EnemywpnPwr, unsigned int myHP, unsigned int time, unsigned int myplrID, unsigned int mywpnPwr);

};
#endif