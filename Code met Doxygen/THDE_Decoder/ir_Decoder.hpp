#include "hwlib.hpp"
#include "rtos.hpp"

struct message{unsigned int plrID; unsigned int data;};

/// \brief
/// Decoder class
/// \details
/// This is a IR-decoder class that inherits from rtos::task
/// The idle, receive_Message and the decode_Message are stored as 3 state_t enum states 
/// The apropriate functions are provided
class ir_Decoder : public rtos::task<>{

enum state_t{idle, receive_Message, decode_Message};

hwlib::target::pin_in tsop_signal  = hwlib::target::pin_in( hwlib::target::pins::d8 );
hwlib::target::pin_out tsop_gnd = hwlib::target::pin_out( hwlib::target::pins::d9 );
hwlib::target::pin_out tsop_vdd = hwlib::target::pin_out( hwlib::target::pins::d10 );

private:
    state_t state = idle;
    rtos::flag flag_sendBitMessage;
    //rtos::pool <unsigned int array[16]> messagePool;

    unsigned int plrID, data;
    
public:
    ir_Decoder():
        task("ir_Decode"),
        flag_sendBitMessage(this, "flag_sendBitMessage"),
        //messagePool("messagePool"),
        plrID(0),
        data(0)
    {}

    unsigned int array[16];

    /// \brief
    /// Return bit from specific position
    /// \details
    /// This function compares the uint16_t variables b and mask 
    /// whilst n specifies the position of which the bits compare with the AND operator
    /// and returns either a 1 or a 0.
    bool getBit(uint16_t b,  int n){
        uint16_t mask = 1 << n;
        if (b & mask)
            return 1;
        else
            return 0;
    }

    /// \brief
    /// Detects pauses
    /// \details
    /// This function returns a 0, 1 or 2 based on unsigned int n 
    /// being within a certain threshold
    unsigned int pauze_detectie(unsigned int n){
        if( n > 600 && n < 1000)
            return 1;
        else if( n > 1400 && n < 1800)
            return 0;
        else
            return 2;
    }   

    /// \brief
    /// Receives IR-message
    /// \details
    /// This function reads bits from tsop_signal.read()
    /// until all 16 bits are read and then it breaks out of the function
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

    /// \brief
    /// Checks XOR
    /// \details
    /// This function XOR's the variable unsigned int n with the one that is five indexes further 
    /// and checks it with the one that is 10 indexes further
    bool xorCheck(unsigned int n){
        if((array[n] ^ array[n + 5]) == array[n + 10])
            return 1;
        else 
            return 0;
    }

    /// \brief
    /// Checks message
    /// \details
    /// This function checks if the first bit is a 1 and if the bit index [11 to 16]
    /// are the XOR bits from bit indexes [1 to 5] ^ [6 to 10]
    bool messageCheck(){
        if(array[0] == 1 && xorCheck(1) && xorCheck(2) && xorCheck(3) && xorCheck(4) && xorCheck(5))
            return 1;
        else 
            return 0;
    }

    /// \brief
    /// Translates message
    /// \details
    /// This function turns bits into integers using the variable exponent 
    /// and adds them to the unsigned int item and then 
    /// returns variable item when all integers are added
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

    /// \brief
    /// Decodes message
    /// \details
    /// This function calls the function translater 
    /// with different parameters to send the decoded message to parameterControl
    message decoding(){
        parameterControl.sendMessage(translator(0), translator(1));
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