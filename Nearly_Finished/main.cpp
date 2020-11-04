#include "hwlib.hpp" 
#include "rtos.hpp"
#include "ir_Decoder.hpp"
#include "parameterControl.hpp"
#include "ir_Encoder.hpp"
#include "KeypadTaak.hpp"
#include "OLED.hpp"
#include "gameControl.hpp"

int main( void ){
	WDT -> WDT_MR = WDT_MR_WDDIS;
    
    hwlib::target::pin_in tsop_signal  = hwlib::target::pin_in( hwlib::target::pins::d8 );
    hwlib::target::pin_out tsop_gnd = hwlib::target::pin_out( hwlib::target::pins::d9 );
    hwlib::target::pin_out tsop_vdd = hwlib::target::pin_out( hwlib::target::pins::d10 );

    hwlib::target::pin_in_out trigger = hwlib::target::pin_in_out(hwlib::target::pins::d34);

    hwlib::target::d2_36kHz ir = hwlib::target::d2_36kHz();
    hwlib::target::pin_out led = hwlib::target::pin_out(hwlib::target::pins::d40);

    hwlib::target::pin_oc out0 = hwlib::target::pin_oc( hwlib::target::pins::a4 );
    hwlib::target::pin_oc out1 = hwlib::target::pin_oc( hwlib::target::pins::a5 );
    hwlib::target::pin_oc out2 = hwlib::target::pin_oc( hwlib::target::pins::a6 );
    hwlib::target::pin_oc out3 = hwlib::target::pin_oc( hwlib::target::pins::a7 );

    hwlib::target::pin_in in0  = hwlib::target::pin_in( hwlib::target::pins::a0 );
    hwlib::target::pin_in in1  = hwlib::target::pin_in( hwlib::target::pins::a1 );
    hwlib::target::pin_in in2  = hwlib::target::pin_in( hwlib::target::pins::a2 );
    hwlib::target::pin_in in3  = hwlib::target::pin_in( hwlib::target::pins::a3 );

    hwlib::target::pin_oc scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
    hwlib::target::pin_oc sda = hwlib::target::pin_oc( hwlib::target::pins::sda );

    ir_Encoder my_Encoder = ir_Encoder();
    OLED screen = OLED();    
    gameControl gameCtrl = gameControl(my_Encoder, screen);
    parameterControl paramCtrl = parameterControl(gameCtrl);
    ir_Decoder test2 = ir_Decoder(paramCtrl, gameCtrl);
    KeypadTaak test3 = KeypadTaak(paramCtrl, screen);

    rtos::run();
}