/// This file contains Doxygen lines
/// \brief
/// Encoder class and Encoder task
/// \details
/// This is a IR-encoder class that inherits from rtos::task
/// This tasks encodes recieved messages and writes them to parameterControl

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
    /// \brief
    /// Initialisation list
    ir_Encoder(ir_Led &my_Led);
    
    /// \brief
    /// Return bit from specific position
    /// \details
    /// This function compares the uint16_t variables b and mask 
    /// whilst n specifies the position of which the bits compare with the AND(&) operator
    /// and returns either a 1 or a 0.
    int getBit(uint16_t b,  int n); 
    
    /// \brief
    /// Returns delay value
    /// \details
    /// This function returns int values based on unsigned int i being a 0 or a 1
    int getDelays(unsigned int i);
    
    /// \brief
    /// Writes message to message pool
    /// \details
    /// This function writes the struct variable x which contains 
    /// the values of unsigned int plrID and data to the message pool
    void sendMessage(unsigned int plrID, unsigned int data);
    
    /// \brief
    /// Encodes message
    /// \details
    /// This function uses a for loop to xor the getbit values of PlrID and data
    /// with the unsigned int variabel to make a 16 bit string
    /// and then returns the 16 bit string    
    int encoding(unsigned int plrID, unsigned int data);
    
    /// \brief
    /// Sends IR-message
    /// \details
    /// This function sends the 16 bit string by flashing a IR-LED
    /// with specific delays in microseconds obtained from the getDelays function
    void ir_Send(unsigned int irBericht);  
};
#endif
