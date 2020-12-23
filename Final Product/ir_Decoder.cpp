#include "ir_Decoder.hpp"

void ir_Decoder::main(){
    for(;;){
        switch(state){
            case idle: {
                message_Receiver();
                auto event = wait(flag_sendBitMessage);
                if(event == flag_sendBitMessage){
                    state = decode_Message; 
                    break;
                }
            } 
            case decode_Message: {
                if(messageCheck() == true)
                    decoding();
                state = idle;
                break;
            }    
            default:break;        
        }
    }
} 

ir_Decoder::ir_Decoder(parameterControl &paramCtrl, gameControl &gameCtrl, ir_Receiver &my_Receiver):
        task(2, "ir_Decoder"),
        flag_sendBitMessage(this, "flag_sendBitMessage"),
        paramCtrl(paramCtrl), 
        gameCtrl(gameCtrl),
        my_Receiver(my_Receiver)    
    {}

unsigned int array[16];

bool ir_Decoder::getBit(uint16_t b,  int n){
    uint16_t mask = 1 << n;
    if (b & mask)
        return 1;
    else
        return 0;
}

unsigned int ir_Decoder::pauze_detectie(unsigned int n){
    if( n > 600 && n < 1000)
        return 0;
    else if( n > 1400 && n < 1800)
        return 1;
    else
        return 2;
}   

void ir_Decoder::message_Receiver(){
    unsigned int idle, arrayCount = 16;
        
    for(;;){
        if(my_Receiver.getCurrentSignal() == 1 && idle > 0 && arrayCount != 0){
            if(pauze_detectie(idle) != 2){
                array[arrayCount - 1] = pauze_detectie(idle);
                arrayCount--;
                idle = 0;
            }
            else if(pauze_detectie(idle) == 2)
                idle = 0;
            else 
                continue;
        }
        else if(my_Receiver.getCurrentSignal() == 0 && arrayCount != 0) 
            idle += 100;
        else if(arrayCount == 0)
            break;
        else 
            continue;
		hwlib::wait_us(100);
	}
    flag_sendBitMessage.set();
    return;
}

bool ir_Decoder::xorCheck(unsigned int n){
    if((array[n] ^ array[n + 5]) == array[n + 10])
        return 1;
    else 
        return 0;
}

bool ir_Decoder::messageCheck(){
    if(array[0] == 1 && xorCheck(1) && xorCheck(2) && xorCheck(3) && xorCheck(4) && xorCheck(5))
        return 1;
    else 
        return 0;
}

unsigned int ir_Decoder::translator(unsigned int itemType){
    unsigned int i, item = 0;
    unsigned int exponent = 1;

    if(itemType == 0)
        i = 1;
    else
        i = 6;
        
    for(unsigned int j = i; j < (i + 5); j++){
        item += array[j] * exponent;
        if(j == (i + 4)){
            return item;
        }
        else
            continue;
        exponent *= 2;
    }
    return 0;
}

void ir_Decoder::decoding(){
    if (translator(0) == 0)
        paramCtrl.sendMessage(translator(1)); // Send Special Command
    else
        gameCtrl.sendMessage(translator(0), translator(1));  // Send Weapon Power/DMG(from plrID)
}