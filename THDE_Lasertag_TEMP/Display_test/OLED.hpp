#include "hwlib.hpp"
#include "rtos.hpp"
namespace target = hwlib::target;

struct hitInfo {unsigned int plrID; unsigned int data; unsigned int hp;};

class oledTaak : public rtos::task<>{
private:
    rtos::flag oledFlag;
    rtos::pool<hitInfo> hitPool;
    rtos::pool<unsigned int> timePool;

    target::pin_oc scl = target::pin_oc( target::pins::scl );
    target::pin_oc sda = target::pin_oc( target::pins::sda );

    hwlib::i2c_bus_bit_banged_scl_sda i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
    hwlib::glcd_oled oled = hwlib::glcd_oled( i2c_bus, 0x3c );
    hwlib::font_default_8x8 f1 = hwlib::font_default_8x8();

    // hwlib::part w1 = hwlib::part(oled, hwlibbxy(0, 0),hwlib::xy(128, 32));
    hwlib::terminal_from scherm = hwlib::terminal_from(oled, f1);

public:
    oledTaak(): 
        task(5, "oledTaak"),
        hitFlag(this, "oledFlag"), 
        plrIDFlag(this, "oledFlag"), 
        wpnPwrFlag(this, "oledFlag"), 
        timeFlag(this, "oledFlag"), 
        hitPool("hitPool"),
        plrIDPool("plrIDPool"),
        wpnPwrPool("wpnPwrPool"),
        timePool("timePool")
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
        scherm << "\t0001" << EnemyID <<"\n";
        scherm << "\t0005" << EnemywpnPwr <<"\n";
        scherm << "\t0010" << myHP <<"\n";
        scherm << "\t0015" << time <<"\n";
        scherm << "\t0020" << myplrID <<"\n";
        scherm << "\t0025" << mywpnPwr <<"\n";
        scherm.flush();
    }

private:
    void main(){
        for(;;){
            auto event = wait{hitFlag, timeFlag, plrIDFlag, wpnPwrFlag};
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
