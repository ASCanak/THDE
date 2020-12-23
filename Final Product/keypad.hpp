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
    unsigned int plrID = 0;
    unsigned int data = 0;
    parameterControl &paramCtrl;
    OLED &screen;

    void main();

public:
    keypad(parameterControl &paramCtrl, OLED &screen);

    void keyPressed(char keyID);
};
#endif 