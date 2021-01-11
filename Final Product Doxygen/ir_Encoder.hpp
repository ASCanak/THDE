#ifndef IR_ENCODER_HPP
#define IR_ENCODER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "ir_Led.hpp"

struct message{unsigned int plrID; unsigned int data;};

class ir_Encoder : public rtos::task<>{

enum state_t{WAIT_Message, encodeMessage};

private:
    state_t state = WAIT_Message;
    rtos::flag flag_sendMessage;
    rtos::pool <message> messagePool;
    ir_Led &my_Led;
    
    void main();

public:
    ir_Encoder(ir_Led &my_Led);

    int getBit(uint16_t b,  int n); 
    
    int getDelays(unsigned int i);

    void sendMessage(unsigned int plrID, unsigned int data);
    
    int encoding(unsigned int plrID, unsigned int data);

    void ir_Send(unsigned int irBericht);  
};
#endif