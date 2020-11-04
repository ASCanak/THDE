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
    
    ir_Encoder my_Encoder = ir_Encoder();
    OLED screen = OLED();
    parameterControl paramCtrl;
    gameControl gameCtrl;

    parameterControl test = parameterControl(gameCtrl);
    gameControl test1 = gameControl(paramCtrl, my_Encoder, screen);
    ir_Decoder test2 = ir_Decoder(paramCtrl, gameCtrl);
    KeypadTaak test3 = KeypadTaak(paramCtrl, screen);
    

    rtos::run();
}