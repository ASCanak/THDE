//this file contains Doxygen lines
///file ir_Decoder.hpp
/// \brief Decoder class and decoder task 
/// \details Decodes received messages and sends them to parameterControl
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
    /// \brief
    /// Initialisation list
    ir_Decoder(parameterControl &paramCtrl, gameControl &gameCtrl, ir_Receiver &my_Receiver);

    /// \brief
    /// Return bit from specific position
    /// \details
    /// This function compares the uint16_t variables b and mask 
    /// whilst n specifies the position of which the bits compare with the AND operator
    /// and returns either a 1 or a 0.
    bool getBit(uint16_t b,  int n);
    
    /// \brief
    /// Detects pauses
    /// \details
    /// This function returns a 0, 1 or 2 based on unsigned int n 
    /// being within a certain threshold
    unsigned int pauze_detectie(unsigned int n);   

    /// \brief
    /// Receives IR-message
    /// \details
    /// This function reads bits from tsop_signal.read()
    /// until all 16 bits are read and then it breaks out of the function
    void message_Receiver();

    /// \brief
    /// Checks XOR
    /// \details
    /// This function XOR's the variable unsigned int n with the one that is five indexes further 
    /// and checks it with the one that is 10 indexes further
    bool xorCheck(unsigned int n);

    /// \brief
    /// Checks message
    /// \details
    /// This function checks if the first bit is a 1 and if the bit index [11 to 16]
    /// are the XOR bits from bit indexes [1 to 5] ^ [6 to 10]
    bool messageCheck();

    /// \brief
    /// Translates message
    /// \details
    /// This function turns bits into integers using the variable exponent 
    /// and adds them to the unsigned int item and then 
    /// returns variable item when all integers are added
    unsigned int translator(unsigned int itemType);

    /// \brief
    /// Decodes message
    /// \details
    /// This function calls the function translater 
    /// with different parameters to send the decoded message to parameterControl
    void decoding();
};
#endif
