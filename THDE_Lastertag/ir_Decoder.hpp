#include "hwlib.hpp"
#include "rtos.hpp"
#include "parameterControl.hpp"

class ir_Decoder : public rtos::task<>{

enum state_t{idle, receive_Message, decode_Message};

hwlib::target::pin_in tsop_signal  = hwlib::target::pin_in( hwlib::target::pins::d8 );
hwlib::target::pin_out tsop_gnd = hwlib::target::pin_out( hwlib::target::pins::d9 );
hwlib::target::pin_out tsop_vdd = hwlib::target::pin_out( hwlib::target::pins::d10 );

private:
    state_t state = idle;
    rtos::flag flag_sendBitMessage;
    //rtos::pool <unsigned int array[16]> messagePool;

    
public:
    ir_Decoder():
        task("ir_Decode"),
        flag_sendBitMessage(this, "flag_sendBitMessage")
        //messagePool("messagePool"),    
    {}

    unsigned int array[16];

    bool getBit(uint16_t b,  int n){
        uint16_t mask = 1 << n;
        if (b & mask)
            return 1;
        else
            return 0;
    }

    unsigned int pauze_detectie(unsigned int n){
        if( n > 600 && n < 1000)
            return 1;
        else if( n > 1400 && n < 1800)
            return 0;
        else
            return 2;
    }   

    void ir_Receiver(){
        tsop_gnd.write( 0 );
        tsop_vdd.write( 1 );
        tsop_gnd.flush();
        tsop_vdd.flush();
        
        unsigned int idle, arrayCount = 0;
        
        for(;;){
            tsop_signal.refresh();
            if(arrayCount == 16)
                break;	
            else if( tsop_signal.read() == 0 && idle > 0 && arrayCount != 16){
                if(pauze_detectie(idle) != 2){
                    array[arrayCount] = pauze_detectie(idle);
                    arrayCount++;
                    idle = 0;
                }
                else if(pauze_detectie(idle) == 2)
                    idle = 0;
                else 
                    continue;
            }
            else
                idle += 100;
            hwlib::wait_us( 100 );
        }
        // for(unsigned int i = 0; i < bitSize; i++){
        //     hwlib::cout << array[i] << " ";
        // }
        // hwlib::cout << "\n";
        flag_sendBitMessage.set();
        return;
    }

    bool xorCheck(unsigned int n){
        if((array[n] ^ array[n + 5]) == array[n + 10])
            return 1;
        else 
            return 0;
    }

    bool messageCheck(){
        if(array[0] == 1 && xorCheck(1) && xorCheck(2) && xorCheck(3) && xorCheck(4) && xorCheck(5))
            return 1;
        else 
            return 0;
    }

    unsigned int translator(unsigned int itemType){
        unsigned int i, item = 0;
        unsigned int exponent = 1;

        if(itemType == 0)
            i = 1;
        else
            i = 6;
            
        for(unsigned int j = i; j < (i + 5); j++){
            item += array[j] * exponent;
            if(j == (i + 4))
                return item;
            
            exponent *= 2;
        }
    }

    void decoding(){
        if (translator(0) == 0)
            parameterControl.sendMessage(translator(0), translator(1)); // Send Special Command
        else
            gameControl.sendMessage(translator(0), translator(1));      // Send Weapon Power(from plrID)
    }

private:
    void main(){
        for(;;){
            switch(state){
                case idle: {
                    ir_Receiver();
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
};