#include "ir_Encoder.hpp"

void ir_Encoder::main(){
    hwlib::cout << "ir_Encoder\n";
    for(;;){
        switch(state){
            case WAIT_Message: {
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

ir_Encoder::ir_Encoder(ir_Led &my_Led):
    task(2, "ir_Encode"),
    flag_sendMessage(this, "flag_sendMessage"),
    messagePool("messagePool"),
    my_Led(my_Led)
{}

int ir_Encoder::getBit(uint16_t b,  int n){
    uint16_t mask = 1 << n;
    if (b & mask)
        return 1;
    else
        return 0;
}   

int ir_Encoder::getDelays(unsigned int i){
    if(i == 1)
        return 1600;
    else
        return 800;
}

void ir_Encoder::sendMessage(unsigned int plrID, unsigned int data){
    message x{plrID, data};
    messagePool.write(x);
    flag_sendMessage.set();
}

int ir_Encoder::encoding(unsigned int plrID, unsigned int data){
    unsigned int exponent = 1;
    unsigned int controleBit = 0;

    for(unsigned int i = 0; i < 5; i++){
        controleBit += (getBit(plrID, i) ^ getBit(data, i)) * exponent;
        exponent *= 2;
    }
    return (1 + (plrID * 2) + (data * 64) + (controleBit * 2048));
}

void ir_Encoder::ir_Send(unsigned int irBericht){    
    for(int i = 15; i >= 0 ; i--){
        my_Led.zetAan();
        hwlib::wait_us(getDelays(getBit(irBericht, i)));

        my_Led.zetUit();
        hwlib::wait_us(getDelays(getBit(irBericht, i) + 1));
    }
    hwlib::wait_ms(3);
    return;
}