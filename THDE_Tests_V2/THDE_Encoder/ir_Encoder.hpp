#include "hwlib.hpp"
#include "rtos.hpp"

struct message{unsigned int plrID; unsigned int data;};

class ir_Encoder : public rtos::task<>{

enum state_t{WAIT_Message, encodeMessage};

hwlib::target::d2_36kHz ir = hwlib::target::d2_36kHz();
hwlib::target::pin_out led = hwlib::target::pin_out(hwlib::target::pins::d40);

private:
    state_t state = WAIT_Message;
    rtos::flag flag_sendMessage;
    rtos::pool <message> messagePool;

    unsigned int plrID, data;
    
public:
    ir_Encoder( unsigned int plrID, unsigned int data ):
        task("ir_Encode"),
        flag_sendMessage(this, "flag_sendMessage"),
        messagePool("messagePool"),
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

    void sendMessage(){ // unsigned int plrID, unsigned int data
        message x{plrID, data};
        messagePool.write(x);
        flag_sendMessage.set();
    }
    
    int encoding(unsigned int plrID, unsigned int data){
        unsigned int exponent = 1;
        unsigned int controleBit = 0;

        for(unsigned int i = 0; i < 5; i++){
            controleBit += (getBit(plrID, i) ^ getBit(data, i)) * exponent;
            exponent *= 2;
        }

        return (1 + (plrID * 2) + (data * 64) + (controleBit * 2048));
    }

    void ir_Send(unsigned int irBericht){
        led.flush();
        ir.flush();
            
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
        hwlib::wait_ms(3);
        
        return;
    }

private:
    void main(){
        for(;;){
            switch(state){
                case WAIT_Message: {
                    sendMessage();
                    auto event = wait(flag_sendMessage);
                    if(event == flag_sendMessage){
                        state = encodeMessage; 
                        break;
                    }
                }
                case encodeMessage: {
                    message X{messagePool.read()};
                    ir_Send(encoding(X.plrID, X.data));
                    state = WAIT_Message;
                    break;
                }    
                default:break;        
            }
        }
    }    
};