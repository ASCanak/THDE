#include "trigger.hpp"

trigger::trigger(hwlib::target::pin_in_out &sw):
    sw(sw)
    {}

bool trigger::triggerRead(){
    return sw.read();
}