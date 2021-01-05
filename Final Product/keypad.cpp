#include "keypad.hpp"

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

keypad::keypad(parameterControl &paramCtrl, OLED &screen):
        task(4,"keypad"),
        keyChannel(this, "keyChannel"),
        plrID(0),
        data(0),
        paramCtrl(paramCtrl),
        screen(screen)
    {}

void keypad::keyPressed(char keyID){
    keyChannel.write(keyID);
}

void keypad::main(){
    hwlib::cout << "keypad\n";
    char keyID = 0;
    for(;;){
        hwlib::cout << "test1, Keypad\n";
        auto key = keypad_Matrix.getc();
        hwlib::cout << "test2, Keypad\n";
        keyPressed(key);
        hwlib::cout << "test3, Keypad\n";
        auto event = wait(keyChannel);
        hwlib::cout << "test4, Keypad\n";

        if(event == keyChannel){
            keyID = keyChannel.read();
            hwlib::cout << keyID << "\n test1.1, Keypad\n";
            if(keyID == keyA){
                hwlib::cout << keyID << "\n test2.1, Keypad\n";
                keyPressed(key);
                auto event = wait(keyChannel);
                if(event == keyChannel){
                    keyID = keyChannel.read();
                    plrID = keyID - 48;
                    if(plrID >= 0 && plrID < 32){
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
                    if(data >= 0 && data < 32 && plrID != 0){
                        screen.write_wpnPwrID(data);
                        paramCtrl.setPlayerInfo(plrID, data);
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