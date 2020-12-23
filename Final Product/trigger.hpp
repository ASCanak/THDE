#ifndef TRIGGER_HPP
#define TRIGGER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

class trigger{

private:
    hwlib::target::pin_in_out &sw;

public:
    trigger(hwlib::target::pin_in_out &sw);

    bool triggerRead();
};
#endif