#include "hwlib.hpp"
#include "rtos.hpp"
#include "parameterControl.hpp"

struct infoPlayer{unsigned int plrID; unsigned int data;};

class gameControl : public rtos::task<>{
private:
    hwlib::target::pin_in_out trigger = hwlib::target::pin_in_out(hwlib::target::pins::d34);

public:

    void getInfo(){
        parameterControl.sendInfo();
    }

    void sendMessage(unsigned int plrID, unsigned int data){
        infoPlayer x{plrID, data};
    }
}