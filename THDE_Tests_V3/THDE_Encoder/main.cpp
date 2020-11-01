#include "hwlib.hpp" 
#include "rtos.hpp"
#include "ir_Encoder.hpp"

int main( void ){
	WDT -> WDT_MR = WDT_MR_WDDIS;
    for(;;){
        ir_Encoder Test(5, 7);
        hwlib::wait_ms(100);
    }
    rtos::run();
}