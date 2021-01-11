#ifndef TRIGGER_HPP
#define TRIGGER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "gameControl.hpp"

/// \brief
/// Trigger class
/// \details
/// This is a trigger class that inherits from rtos::task
/// The apropriate functions are provided
class trigger : public rtos::task<>{

private:
    hwlib::target::pin_in_out &sw;
    
    gameControl &gameCtrl;

    void main();

public:
    trigger(hwlib::target::pin_in_out &sw, gameControl &gameCtrl);
};
#endif
