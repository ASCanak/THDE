#ifndef TRIGGER_HPP
#define TRIGGER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "gameControl.hpp"

class trigger : public rtos::task<>{

private:
    hwlib::target::pin_in_out &sw;
    
    gameControl &gameCtrl;

    void main();

public:
    trigger(hwlib::target::pin_in_out &sw, gameControl &gameCtrl);

    bool triggerRead();
};
#endif