#include "hwlib.hpp"
#include "rtos.hpp"

class keypadTaak : public rtos::task<>{
   hwlib::target::pin_oc out0 = hwlib::target::pin_oc( hwlib::target::pins::a4 );
   hwlib::target::pin_oc out1 = hwlib::target::pin_oc( hwlib::target::pins::a5 );
   hwlib::target::pin_oc out2 = hwlib::target::pin_oc( hwlib::target::pins::a6 );
   hwlib::target::pin_oc out3 = hwlib::target::pin_oc( hwlib::target::pins::a7 );

   hwlib::target::pin_in in0  = hwlib::target::pin_in( hwlib::target::pins::a0 );
   hwlib::target::pin_in in1  = hwlib::target::pin_in( hwlib::target::pins::a1 );
   hwlib::target::pin_in in2  = hwlib::target::pin_in( hwlib::target::pins::a2 );
   hwlib::target::pin_in in3  = hwlib::target::pin_in( hwlib::target::pins::a3 );

   hwlib::port_oc_from out_port = hwlib::port_oc_from( out0, out1, out2, out3 );
   hwlib::port_in_from in_port  = hwlib::port_in_from( in0,  in1,  in2,  in3  );
   hwlib::port_in_from matrix   = hwlib::matrix_of_switches( out_port, in_port );
   hwlib::port_in_from keypad   = hwlib::keypad< 16 >( matrix, "123A456B789C*0#D" );
   hwlib::istream kbd;

   enum keys{key1, key2, key3, keyA, 
           key4, key5, key6, keyB, 
           key7, key8, key9, keyC, 
           keySter, key0, keyHash, keyD};
        
            key1 = '1';
            key2 = '2';
            key3 = '3';
            keyA = 'A';
            key4 = '4';
            key5 = '5';
            key6 = '6';
            keyB = 'B';
            key7 = '7';
            key8 = '8';
            key9 = '9';
            keyC = 'C';
            keySter = '*';
            key0 = '0';
            keyHash = '#';
            keyD = 'D';


private:
    rtos::channel<char,16> keyChannel;
    unsigned int plrID = 0;
    unsigned int data = 0;
    parameterControl &paramCtrl;
public:
    task(2,"keypadTaak"),
    keyChannel("keyChannel"),
    plrID(0),
    data(0),
    paramCtrl(paramCtrl)
    {}

    void keyPressed(char keyID){keyChannel.write(keyID);}

    void keyValues(unsigned int n, unsigned int type){
        if(type == 1){

        }
        else if(type == 2){

        }
        else{

        }
    }

private:
    void main( void){
        keys keyID;
        for(;;){
            auto key = kbd.getc();
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
                            paramCtrl.sendKeyPress(plrID, data);
                        }
                        else 
                            continue;
                    }
                }

                else if(keyID == keyB){
                    keyPressed(key);
                    auto event = wait(keyChannel);
                    if(event == keyChannel){
                        keyID = keyChannel.read();
                        data = keyID - 48;
                        if(data >= 0 && data <= 32){
                            paramCtrl.sendKeyPress(plrID, data);
                        }
                    }
                    else 
                        continue;
                }

                else if(keyID == keyC){
                    keyPressed(key);
                    auto event = wait(keyChannel);
                    if(event == keyChannel){
                        keyID = keyChannel.read();
                        plrID = 0;
                        data = keyID - 48;
                        keyPressed(key);
                        if(data >= 0 &&  <= 90 && ){
                            initGame.setplayerInfo(plrID, data);
                        }
                    }
                    
                } 

            }
        }
    }

}; 