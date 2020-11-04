#ifndef KEYPADTAAK_HPP
#define KEYPADTAAK_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "parameterControl.hpp"
#include "OLED.hpp"

class KeypadTaak : public rtos::task<>{
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
    hwlib::keypad<16> keypad    = hwlib::keypad<16>( matrix, "123A456B789C*0#D" );

    char key1 = '1';
    char key2 = '2';
    char key3 = '3';
    char keyA = 'A';
    char key4 = '4';
    char key5 = '5';
    char key6 = '6';
    char keyB = 'B';
    char key7 = '7';
    char key8 = '8';
    char key9 = '9';
    char keyC = 'C';
    char keySter = '*';
    char key0 = '0';
    char keyHash = '#';
    char keyD = 'D';

private:
    rtos::channel<char,16> keyChannel;
    unsigned int plrID = 0;
    unsigned int data = 0;
    parameterControl &paramCtrl;
    OLED &screen;
public:
    KeypadTaak(parameterControl &paramCtrl, OLED &screen):
        task(2,"KeypadTaak"),
        keyChannel(this, "keyChannel"),
        plrID(0),
        data(0),
        paramCtrl(paramCtrl),
        screen(screen)
    {}

    void keyPressed(char keyID){keyChannel.write(keyID);}

private:
    void main( void){
        char keyID;
        for(;;){
            auto key = keypad.getc();
            keyPressed(key);
            auto event = wait(keyChannel);

            if(event == keyChannel){
                keyID = keyChannel.read();
                if(keyID == keyA){
                    keyPressed(key);
                    auto event = wait(keyChannel);
                    if(event == keyChannel){
                        keyID = keyChannel.read();
                        plrID = keyID - 48;
                        if(plrID >= 0 && plrID <= 32){
                            screen.write_plrID(plrID);
                            continue;
                        }
                        else{ 
                            keyID = 0;
                            continue;
                        }
                    }
                }

                else if(keyID == keyB){
                    keyPressed(key);
                    auto event = wait(keyChannel);
                    if(event == keyChannel){
                        keyID = keyChannel.read();
                        data = keyID - 48;
                        if(data >= 0 && data <= 32 && plrID != 0){
                            screen.write_wpnPwrID(data);
                            paramCtrl.setplayerInfo(plrID, data);
                            plrID = 0;
                            data = 0;
                        }
                        else{
                            keyID = 0;
                            continue;
                        }
                    }
                }

                // else if(keyID == keyC){
                //     keyPressed(key);
                //     auto event = wait(keyChannel);
                //     if(event == keyChannel){
                //         keyID = keyChannel.read();
                //         plrID = 0;
                //         data = keyID - 48;
                //         keyPressed(key);
                //         if(data >= 0 &&  <= 90 && ){
                //             initGame.setplayerInfo(plrID, data);
                //         }
                //         else 
                //             continue;
                //     }  
                //} 

            }
        }
    }
}; 

#endif