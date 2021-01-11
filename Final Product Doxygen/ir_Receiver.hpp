/// This file contains Doxygen lines
/// \brief
/// ir-Reciever class
/// \details
/// This class recieves signals from the ir-led 

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
    
    /// \brief
    /// Gets current sgnal
    /// \details
    /// This function reads the current signal from the ir-led
    bool getCurrentSignal();
};

#endif
