#ifndef IR_DECODER_HPP
#define IR_DECODER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "parameterControl.hpp"
#include "gameControl.hpp"
#include "ir_Receiver.hpp"

class ir_Decoder : public rtos::task<>{

enum state_t{idle, receive_Message, decode_Message};

private:
    state_t state = idle;
    rtos::flag flag_sendBitMessage;
    
    parameterControl &paramCtrl;
    gameControl &gameCtrl;
    ir_Receiver &my_Receiver;
    
    void main();

public:
    ir_Decoder(parameterControl &paramCtrl, gameControl &gameCtrl, ir_Receiver &my_Receiver);

    bool getBit(uint16_t b,  int n);

    unsigned int pauze_detectie(unsigned int n);   

    void message_Receiver();

    bool xorCheck(unsigned int n);

    bool messageCheck();

    unsigned int translator(unsigned int itemType);

    void decoding();
};
#endif