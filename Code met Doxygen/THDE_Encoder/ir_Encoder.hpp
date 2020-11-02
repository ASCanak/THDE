#include "hwlib.hpp"
#include "rtos.hpp"

///@file

struct message{unsigned int plrID; unsigned int data;};

/// \brief
/// Encoder class
/// \details
/// This is a IR-encoder class that inherits from rtos::task
/// The WAIT_message and the encodemessage are stored as 2 state_t enum states 
/// The apropriate functions are provided
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

    /// \brief
    /// Return bit from specific position
    /// \details
    /// This function compares the uint16_t variables b and mask 
    /// whilst n specifies the position of which the bits compare with the AND(&) operator
    /// and returns either a 1 or a 0.
    int getBit(uint16_t b,  int n){
        uint16_t mask = 1 << n;
        if (b & mask)
            return 1;
        else
            return 0;
    }   

    /// \brief
    /// Returns delay value
    /// \details
    /// This function returns int values based on unsigned int i being a 0 or a 1
    int getDelays(unsigned int i){
        if(i == 1)
            return 1600;
        else
            return 800;
    }

    /// \brief
    /// Writes message to message pool
    /// \details
    /// This function writes the struct variable x which contains 
    /// the values of unsigned int plrID and data to the message pool
    void sendMessage(){
        message x{plrID, data};
        messagePool.write(x);
        flag_sendMessage.set();
    }
    
    /// \brief
    /// encodes message
    /// \details
    /// This function uses a for loop to xor the getbit values of PlrID and data
    /// with the unsigned int variabel to make a 16 bit string
    /// and then returns the 16 bit string
    int encoding(unsigned int plrID, unsigned int data){
        unsigned int exponent = 1;
        unsigned int controleBit = 0;

        for(unsigned int i = 0; i < 5; i++){
            controleBit += (getBit(plrID, i) ^ getBit(data, i)) * exponent;
            exponent *= 2;
        }

        return (1 + (plrID * 2) + (data * 64) + (controleBit * 2048));
    }

    /// \brief
    /// Sends IR-message
    /// \details
    /// This function sends the 16 bit string by flashing a IR-LED
    /// with specific delays in microseconds obtained from the getDelays function
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
