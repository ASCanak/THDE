/// This file contains Doxygen lines
/// \brief
/// Ir_led class
/// \details
/// This is a Ir-led class that inherits from rtos::task
/// This class turns the Led on or off
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

    /// \brief
    /// Turns led on
    /// \details
    /// This function turns the led on
    void zetAan();

    /// \brief
    /// Turns led off 
    /// \details
    /// This function turns the led off
    void zetUit();
};
#endif
