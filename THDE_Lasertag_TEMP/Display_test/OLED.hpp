#include "hwlib.hpp"
#include "rtos.hpp"
namespace target = hwlib::target;

class oledTaak : public rtos::task<>{
private:
rtos::flag oledFlag;
rtos::pool<char> oledPool;

public:
    oledTaak(): task("oledTaak"), 
    oledFlag(this, "oledFlag"), 
    oledPool("oledPool")
    {}

    void write_Stats(unsigned int plrID, unsigned int data, unsigned int hp){
        oledPool.write(plrID, data, hp); oledFlag.set();
        hwlib::cout << "Hit by plrID: " << plrID << "With wpnPwr: " << data << "HP left: << hp << \n";
        scherm1 << "\f" << oledPool.read() << "\n";
    }
         void write_Time(unsigned int time){
         oledPool.write(text); oledFlag.set();
         hwlib::cout << "Remaining time: " << "\n";
         scherm2 << "\f" << oledPool.read() << "\n";
    }


private:
    void main(){ // auto kan niet 
        auto scl = target::pin_oc( target::pins::scl );
        auto sda = target::pin_oc( target::pins::sda );

        auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );

        auto oled = hwlib::glcd_oled( i2c_bus, 0x3c );
        auto f2 = hwlib::font_default_8x8();
        auto scherm1 = hwlib::terminal_from(oled, f2);
    }
};
