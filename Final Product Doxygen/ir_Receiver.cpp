#include "ir_Receiver.hpp"

ir_Receiver::ir_Receiver(hwlib::target::pin_in &tsop_signal, hwlib::target::pin_out &tsop_gnd, hwlib::target::pin_out &tsop_vdd):
    tsop_signal(tsop_signal),
    tsop_gnd(tsop_gnd),
    tsop_vdd(tsop_vdd)
    {}

bool ir_Receiver::getCurrentSignal(){
    tsop_gnd.write(0);
    tsop_vdd.write(1);
    tsop_gnd.flush();
    tsop_vdd.flush();
    
    tsop_signal.refresh();
    return tsop_signal.read();
}