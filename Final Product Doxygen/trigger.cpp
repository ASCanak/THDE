  
#include "trigger.hpp"

void trigger::main(){
    hwlib::cout << "trigger\n";
    for(;;){
        if(sw.read() != 1){
            gameCtrl.set_triggerFlag();
            hwlib::wait_ms(gameCtrl.cooldown());
        }
        hwlib::wait_ms(10);
    }
}

trigger::trigger(hwlib::target::pin_in_out &sw, gameControl &gameCtrl):
    task(1, "trigger"),
    sw(sw),
    gameCtrl(gameCtrl)
{}
