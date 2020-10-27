#include "hwlib.hpp"
#include <bitset>
using namespace std;

int getBit(uint32_t b,  int n){
    uint32_t mask = 1 << n;
    if (b & mask)
        return 1;
    else
        return 0;
}

double getDelays(unsigned int i){
    if(i == 1)
        return 1.6;
    else
        return 0.8;
}

int main( void ){
    // IR output LED
    auto ir = hwlib::target::d2_36kHz(); //verandert naar 38kHz
    // red output LED
    auto red = hwlib::target::pin_out( hwlib::target::pins::d51 );
    // switch which enables the 38 kHz output
    auto sw = hwlib::target::pin_in( hwlib::target::pins::d45 );
    
    unsigned int irBericht = 0b10010111011010001001011101101000; 
    
    for(;;){
        sw.refresh();
        
        while(! sw.read()){
            red.write(1);
            ir.write(1);
            ir.flush();
            red.flush();
            
            hwlib::wait_ms(9);
            
            red.write(0);
            ir.write(0);
            ir.flush();
            
            hwlib::wait_ms(4.5);
            
            for(int i = 31; i >= 0 ; i--){
                red.write(1);
                ir.write(1);
                ir.flush();

                hwlib::wait_ms(getDelays(getBit(irBericht, i)));

                red.write(0);
                ir.write(0);
                ir.flush();
                
                hwlib::wait_ms(getDelays(getBit(irBericht, i) + 1));
            }
            red.write(1);
            ir.write(1);
            ir.flush();
            
            hwlib::wait_ms(0.8);
            
            red.write(0);
            ir.write(0);
            ir.flush();
            
            hwlib::wait_ms(3);
        }
    }
    return 0;
}
