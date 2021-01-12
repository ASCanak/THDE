#ifndef OLED_HPP
#define OLED_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

struct hitInfo {unsigned int plrID; unsigned int data; unsigned int hp; unsigned int messageID;};
struct messageInfo {unsigned int message; unsigned int number;};

class OLED : public rtos::task<>{
private:
    hwlib::target::pin_oc &scl;
    hwlib::target::pin_oc &sda;

    hwlib::i2c_bus_bit_banged_scl_sda i2c_bus;
    hwlib::glcd_oled oled;
    hwlib::font_default_8x8 f1;
    hwlib::window_part_t w1;
    hwlib::window_part_t w2;
    hwlib::terminal_from scherm;
    hwlib::terminal_from scherm2;
    
    rtos::pool<hitInfo> hitPool; rtos::flag hitFlag;
    rtos::pool<messageInfo> messagePool; rtos::flag messageFlag;
    rtos::pool<unsigned int> plrIDPool; rtos::flag plrIDFlag;
    rtos::pool<unsigned int> wpnPwrPool; rtos::flag wpnPwrFlag;
    rtos::pool<unsigned int> minPool; rtos::flag minFlag;
    rtos::pool<unsigned int> secPool; rtos::flag secFlag;  

    void main();
    
public:
    OLED(hwlib::target::pin_oc &scl, hwlib::target::pin_oc &sda);
    void write_hitInfo(unsigned int plrID, unsigned int data, unsigned int hp);
    void write_message(unsigned int messageID, unsigned int number);
    void write_Min(unsigned int updated_Time);
    void write_Sec(unsigned int updated_Time);
    void write_plrID(unsigned int plrID);
    void write_wpnPwrID(unsigned int data);
    void initialize_OLED();
    void display_HUD(unsigned int myHP, unsigned int min, unsigned int sec, unsigned int myplrID, unsigned int mywpnPwr);
    void display_Message(unsigned int EnemyID, unsigned int EnemywpnPwr, unsigned int messageID, unsigned int number);
};
#endif