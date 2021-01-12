/// This file contains Doxygen lines
/// \brief
/// OLED class
/// \details
/// This is an OLED class that inherits from rtos::task
/// Allows data to be shown on the OLED

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
    rtos::pool<unsigned int> minPool; rtos::flag minFlag;
    rtos::pool<unsigned int> secPool; rtos::flag secFlag;  

    unsigned int min, seconds, plrID, wpnPwr;

    void main();
    
public:
    OLED(hwlib::target::pin_oc &scl, hwlib::target::pin_oc &sda);
    
    /// \brief
    /// Writes the event info to a pool
    /// \details
    /// This function makes a struct out of the four given parameters and writes that struct to hitpool and sets hitflag
    void write_eventInfo(unsigned int plrID, unsigned int data, unsigned int hp, unsigned int messageID);

    
    /// \brief
    /// Writes the total minutes to a pool
    /// \details
    /// This function writes the updated_Time parameter to minpool and sets minflag
    void write_Min(unsigned int updated_Time);
    
    /// \brief
    /// Writes the total seconds to a pool
    /// \details
    /// This function writes the updated_Time parameter to secpool and sets secflag
    void write_Sec(unsigned int updated_Time);
    
    /// \brief
    /// Writes the plrID to a pool
    /// \details
    /// This function write the user's plrID to plrIDpool and sets plrIDflag
    void write_plrID(unsigned int plrID);
    
    /// \brief
    /// Writes the wpnPwrID to a pool
    /// \details
    /// This function write the user's wpnPwrID to wpnPwrIDpool and sets wpnPwrIDflag
    void write_wpnPwrID(unsigned int data);
    
    /// \brief
    /// Shows all necessary infomation on the OLED 
    /// \details
    /// This function writes all the necessary infomation on to the OLED
    void write_to_Oled(unsigned int EnemyID, unsigned int EnemywpnPwr, unsigned int myHP, unsigned int min, unsigned int sec, unsigned int myplrID, unsigned int mywpnPwr);
};
#endif
