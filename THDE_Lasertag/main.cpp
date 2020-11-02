#include "hwlib.hpp" 
#include "rtos.hpp"
#include "ir_Decoder.hpp"

int main( void ){
	WDT -> WDT_MR = WDT_MR_WDDIS;
    for(;;){
        ir_Decoder();
        hwlib::wait_ms(100);
    }
}