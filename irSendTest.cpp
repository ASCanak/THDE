#include "hwlib.hpp"
#include <iostream>
#include <bitset>
using namespace std;

int getBit(uint32_t b,  int n){
    uint32_t mask = 1 << n;
    if (b & mask)
        return 1;
    else
        return 0;
}

double getOnTime(unsigned int i){
    if(int i == 1)
        return 1.6;
    else if(int i == 0)
        return 0.8;
}

double getOffTime(unsigned int i){
    if(int i == 1)
        return 0.8
    else if(int i == 0)
        return 1.6
}

int main( void ){
    // IR output LED
    auto ir = hwlib::target::d2_36kHz();
    // red output LED
    auto red = hwlib::target::pin_out( hwlib::target::pins::d42 );
    // switch which enables the 36 kHz output
    auto sw = hwlib::target::pin_in( hwlib::target::pins::d43 );
    
    unsigned int irBericht = 0b10011111100111111001111110011111;
    
    for(;;){
        sw.refresh();
        
        while(! sw.read()){
            ir.write(1);
            red.write(1);
            
            hwlib::wait_ms(9);
            
            ir.write(0);
            red.write(0);
            
            hwlib::wait_ms(4.5);
            
            for(int i = 31; i >= 0 ; i--){
                ir.write(1);
                red.write(1);

                hwlib::wait_ms(getOnTime(getBit(irBericht, i)));

                red.write(0);
                ir.write(0);
                
                hwlib::wait_ms(getOffTime(getBit(irBericht, i)));
            }
            hwlib::wait_ms(4);
        }
    }
    return 0;
}
