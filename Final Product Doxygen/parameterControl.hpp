/// This file contains Doxygen lines
/// \brief
/// ParameterControl class 
/// \details
/// This class sends the recieved data to the entity class and gives gameControl the start signal

#ifndef PARAMETERCONTROL_HPP
#define PARAMETERCONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "gameControl.hpp"
#include "gameInfoEntity.hpp"

class gameControl;
class parameterControl{

private:
    gameControl &gameCtrl;
    gameInfoEntity &gameEntity;

public:
    parameterControl(gameControl &gameCtrl, gameInfoEntity &gameEntity);
    
    /// \brief
    /// Sends data to a different class
    /// \details
    /// This function sends either the startgame data to the gameControl class 
    /// or sends the gameTime data to the entity class.
    void sendMessage(unsigned int data);
    
    /// \brief
    /// Sets plrID
    /// \details
    /// This function sends the plrID to the entity    
    void set_plrID(unsigned int plrID);
     
    /// \brief
    /// Sets wpnPwrID
    /// \details
    /// This function sends the wpnPwrID to the entity 
    void set_wpnPwr(unsigned int data);
};

#endif
