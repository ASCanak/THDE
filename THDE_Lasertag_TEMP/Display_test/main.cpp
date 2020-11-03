#include "hwlib.hpp"
#include "OLED.hpp"


int main(){
    auto display = oledTaak();
    rtos::run();
}