/// This file contains Doxygen lines
/// \brief
/// keypad class and keypad task
/// \details
/// This is a keypad class that inherits from rtos::task
/// This keypad task makes it so that the user can input and save their plrID and wpnPwrID,
/// also makes it available for the game master to input the gametime and start the game.

#ifndef KEYPAD_HPP
#define KEYPAD_HPP

#include "rtos.hpp"
#include "parameterControl.hpp"
#include "OLED.hpp"

class keypad : public rtos::task<> {
    hwlib::target::pin_oc out0 = hwlib::target::pin_oc( hwlib::target::pins::a4 );
    hwlib::target::pin_oc out1 = hwlib::target::pin_oc( hwlib::target::pins::a5 );
    hwlib::target::pin_oc out2 = hwlib::target::pin_oc( hwlib::target::pins::a6 );
    hwlib::target::pin_oc out3 = hwlib::target::pin_oc( hwlib::target::pins::a7 );

    hwlib::target::pin_in in0  = hwlib::target::pin_in( hwlib::target::pins::a0 );
    hwlib::target::pin_in in1  = hwlib::target::pin_in( hwlib::target::pins::a1 );
    hwlib::target::pin_in in2  = hwlib::target::pin_in( hwlib::target::pins::a2 );
    hwlib::target::pin_in in3  = hwlib::target::pin_in( hwlib::target::pins::a3 );

    hwlib::port_oc_from_pins_t out_port = hwlib::port_oc_from( out0, out1, out2, out3 );
    hwlib::port_in_from_pins_t in_port  = hwlib::port_in_from( in0,  in1,  in2,  in3  );
    hwlib::matrix_of_switches matrix    = hwlib::matrix_of_switches( out_port, in_port );
    hwlib::keypad<16> keypad_Matrix     = hwlib::keypad<16>( matrix, "123A456B789C*0#D" );

private:
    rtos::channel<char,16> keyChannel;
    unsigned int plrID, wpnPwr, data, time;
    char keyID = '\0';
    parameterControl &paramCtrl;
    OLED &screen;

    void main();

public:
    keypad(parameterControl &paramCtrl, OLED &screen);
};
#endif 
