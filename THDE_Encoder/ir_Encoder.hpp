#include "hwlib.hpp"
#include "rtos.hpp"

class ir_Encoder : public rtos::task<>{

enum state_t = {WAIT_Message, encodeMessage};
auto ir = hwlib::target::d2_36kHz();

private:
    state_t state = WAIT_Message;
    rtos::flag flag_sendMessage;

    unsigned int data, plrID;
    
public:
    ir_Encoder( unsigned int plrID, unsigned int data ):
        plrID(plrID),
        data(data)
    {}

    int getBit(uint16_t b,  int n){
        uint16_t mask = 1 << n;
        if (b & mask)
            return 1;
        else
            return 0;
    }   
    
    int getDelays(unsigned int i){
        if(i == 1)
            return 1600;
        else
            return 800;
    }

    int encoding(unsigned int plrID, unsigned int data){
        unsigned int exponent = 1;
        unsigned int controleBit = 0;

        for(unsigned int i = 0; i < 5; i++){
            controleBit += (getBit(plrID, i) ^ getBit(data, i)) * exponent;
            exponent *= 2;
        }

        return (1 + (plrID * 2) + (data * 64) + (controleBit * 2048))
    }

    void ir_Send(hwlib::target::pin_out &led){
        while(! sw.read()){
            led.write(1);
            ir.write(1);
            ir.flush();
            led.flush();
            
            hwlib::wait_ms(9);
            
            led.write(0);
            ir.write(0);
            ir.flush();
            
            hwlib::wait_us(4500);
            
            for(int i = 15; i >= 0 ; i--){
                led.write(1);
                ir.write(1);
                ir.flush();

                hwlib::wait_us(getDelays(getBit(irBericht, i)));

                led.write(0);
                ir.write(0);
                ir.flush();
                
                hwlib::wait_us(getDelays(getBit(irBericht, i) + 1));
            }
            led.write(1);
            ir.write(1);
            ir.flush();
            
            hwlib::wait_us(800);
            
            led.write(0);
            ir.write(0);
            ir.flush();
            
            hwlib::wait_ms(3);
        }
        return;
    }    
}