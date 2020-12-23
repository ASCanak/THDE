#ifndef IR_LED_HPP
#define IR_LED_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

class ir_Led{

private:
    hwlib::target::d2_36kHz &ir;
    hwlib::target::pin_out &led;

public:
    ir_Led(hwlib::target::d2_36kHz &ir, hwlib::target::pin_out &led);

    void zetAan();

    void zetUit();
};
#endif