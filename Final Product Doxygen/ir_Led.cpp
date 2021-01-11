#include "ir_Led.hpp"

ir_Led::ir_Led(hwlib::target::d2_36kHz &ir, hwlib::target::pin_out &led):
    ir(ir),
    led(led)
    {}

void ir_Led::zetAan(){
    led.write(1);
    ir.write(1);
    led.flush();
    ir.flush();
}

void ir_Led::zetUit(){
    led.write(0);
    ir.write(0);
    led.flush();
    ir.flush();        
}