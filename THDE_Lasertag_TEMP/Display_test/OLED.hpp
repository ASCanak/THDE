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

    void write_PlrID(char text){
        oledPool.write(text); oledFlag.set();
        hwlib::cout << "PlrID: " << "\n";
        scherm1 << "\f" << oledPool.read() << "\n";
    }
    //     void write_Wpnpwr(char text){
    //     oledPool.write(text); oledFlag.set();
    //     hwlib::cout << "Wpnpwr: " << "\n";
    //     scherm2 << "\f" << oledPool.read() << "\n";
    // }
    //     void write_Tijd(char text){
    //     oledPool.write(text); oledFlag.set();
    //     hwlib::cout << "Tijd: " << "\n";
    //     scherm3 << "\f" << oledPool.read() << "\n";
    // }

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