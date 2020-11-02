#include "hwlib.hpp"
#include "rtos.hpp"

class keypadTaak : public rtos::task<>{

   hwlib::target::pin_oc out0 = target::pin_oc( target::pins::a0 );
   hwlib::target::pin_oc out1 = target::pin_oc( target::pins::a1 );
   hwlib::target::pin_oc out2 = target::pin_oc( target::pins::a2 );
   hwlib::target::pin_oc out3 = target::pin_oc( target::pins::a3 );

   hwlib::target::pin_in in0  = hwlib::target::pin_in( target::pins::a4 );
   hwlib::target::pin_in in1  = hwlib::target::pin_in( target::pins::a5 );
   hwlib::target::pin_in in2  = hwlib::target::pin_in( target::pins::a6 );
   hwlib::target::pin_in in3  = hwlib::target::pin_in( target::pins::a7 );
   
   hwlib::port_oc_from out_port = hwlib::port_oc_from( out0, out1, out2, out3 );
   hwlib::port_in_from in_port  = hwlib::port_in_from( in0,  in1,  in2,  in3  );
   hwlib::port_in_from matrix   = hwlib::matrix_of_switches( out_port, in_port );
   hwlib::port_in_from keypad   = hwlib::keypad< 16 >( matrix, "123A456B789C*0#D" );

public:
    keypadTaak():
    task(2,"keypadTaak"),
    keypadChannel("keypadChannel")
    {}

};