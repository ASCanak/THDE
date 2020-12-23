#include "hwlib.hpp" 
#include "rtos.hpp"

#include "gameControl.hpp"
#include "parameterControl.hpp"

#include "ir_Decoder.hpp"
#include "ir_Receiver.hpp"

#include "ir_Encoder.hpp"
#include "ir_Led.hpp"

#include "keypad.hpp"
#include "OLED.hpp"
#include "trigger.hpp"

#include "gameInfoEntity.hpp"

int main( void ){
	WDT -> WDT_MR = WDT_MR_WDDIS; //Kill the Watchdog

    hwlib::target::pin_in_out sw = hwlib::target::pin_in_out( hwlib::target::pins::d34 );

    hwlib::target::d2_36kHz ir = hwlib::target::d2_36kHz();
    hwlib::target::pin_out led = hwlib::target::pin_out(hwlib::target::pins::d40);

    hwlib::target::pin_in tsop_signal = hwlib::target::pin_in( hwlib::target::pins::d8 );
    hwlib::target::pin_out tsop_gnd   = hwlib::target::pin_out( hwlib::target::pins::d9 );
    hwlib::target::pin_out tsop_vdd   = hwlib::target::pin_out( hwlib::target::pins::d10 );

    hwlib::target::pin_oc scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
    hwlib::target::pin_oc sda = hwlib::target::pin_oc(hwlib::target::pins::sda);

    trigger my_Trigger = trigger(sw);
    ir_Led my_Led = ir_Led(ir, led);
    ir_Receiver my_Receiver = ir_Receiver(tsop_signal, tsop_gnd, tsop_vdd);
    OLED screen = OLED(scl, sda);  
    ir_Encoder my_Encoder = ir_Encoder(my_Led);
    gameInfoEntity my_Entity = gameInfoEntity();
    gameControl gameCtrl = gameControl(my_Encoder, screen, my_Trigger, my_Entity);
    parameterControl paramCtrl = parameterControl(gameCtrl, my_Entity);
    ir_Decoder my_Decoder = ir_Decoder(paramCtrl, gameCtrl, my_Receiver);
    keypad my_Keypad = keypad(paramCtrl, screen);

    rtos::run();
}