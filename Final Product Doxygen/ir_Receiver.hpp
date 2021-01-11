#ifndef IR_RECEIVER_HPP
#define IR_RECEIVER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

class ir_Receiver{

private:
    hwlib::target::pin_in &tsop_signal;
    hwlib::target::pin_out &tsop_gnd;
    hwlib::target::pin_out &tsop_vdd;

public:
    ir_Receiver(hwlib::target::pin_in &tsop_signal, hwlib::target::pin_out &tsop_gnd, hwlib::target::pin_out &tsop_vdd);
    
    bool getCurrentSignal();
};

#endif