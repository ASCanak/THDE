#include "hwlib.hpp"
#include "rtos.hpp"
namespace target = hwlib::target;

struct hitInfo {unsigned int plrID; unsigned int data; unsigned int hp;};

class oledTaak : public rtos::task<>{
private:
rtos::flag oledFlag;
rtos::pool<hitInfo> hitPool;
rtos::pool<unsigned int> timePool;

public:
    oledTaak(): 
        task(5, "oledTaak"),
        oledFlag(this, "oledFlag"), 
        oledPool("oledPool")
    {}

    void write_Stats(unsigned int plrID, unsigned int data, unsigned int hp){
        hitInfo x{plrID, data, hp};
        hitPool.write(x); oledFlag.set();
        hwlib::cout << "Hit by plrID: " << plrID << "With wpnPwr: " << data << "HP left: << hp << \n";
        scherm1 << "\f" << hitPool.read() << "\n";
    }
    void write_Time(unsigned int time){
         timePool.write(time); oledFlag.set();
         hwlib::cout << "Remaining time: " << "\n";
         scherm2 << "\f" << timePool.read() << "\n";
    }
    void 


private:
    void main(){ // auto kan niet 
        target::pin_oc scl = target::pin_oc( target::pins::scl );
        target::pin_oc sda = target::pin_oc( target::pins::sda );

        hwlib::i2c_bus_bit_banged_scl_sda i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );

        hwlib::glcd_oled oled = hwlib::glcd_oled( i2c_bus, 0x3c );
        hwlib::font_default_8x8 f2 = hwlib::font_default_8x8();
        hwlib::terminal_from scherm1 = hwlib::terminal_from(oled, f2);
    }
};
