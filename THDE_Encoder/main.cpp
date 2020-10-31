#include "hwlib.hpp" 
#include "ir_Encoder.hpp"

int main( void ){
	for(;;){
        ir_Encoder Test(5, 7);
        hwlib::wait_ms(100);
    }
}