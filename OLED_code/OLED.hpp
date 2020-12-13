#ifndef OLED_HPP
#define OLED_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "parameterControl.hpp"
#include "gameControl.hpp"
//#include "initGame.hpp"

struct hitInfo {unsigned int plrID; unsigned int data; unsigned int hp;};

hwlib::i2c_bus_bit_banged_scl_sda i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
hwlib::glcd_oled oled = hwlib::glcd_oled( i2c_bus, 0x3c );
hwlib::font_default_8x8 f1 = hwlib::font_default_8x8();

hwlib::window_part_t w1 = hwlib::part(oled, hwlib::xy(0, 0), hwlib::xy(128, 32));
hwlib::terminal_from scherm = hwlib::terminal_from(w1, f1);

class OLED : public rtos::task<>{

private:
    rtos::pool<hitInfo> hitPool; rtos::flag hitFlag;
    rtos::pool<unsigned int> plrIDPool; rtos::flag plrIDFlag;
    rtos::pool<unsigned int> wpnPwrPool; rtos::flag wpnPwrFlag;
    rtos::pool<unsigned int> timePool; rtos::flag timeFlag; 

    void main();
    
public:

    void write_HitInfo(unsigned int plrID, unsigned int data, unsigned int hp);
    void write_Time(unsigned int time);
    void write_plrID(unsigned int plrID);
    void write_wpnPwrID(unsigned int data);
    void write_to_Oled(unsigned int EnemyID, unsigned int EnemywpnPwr, unsigned int myHP, unsigned int time, unsigned int myplrID, unsigned int mywpnPwr);


#endif