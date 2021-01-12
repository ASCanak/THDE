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
        task(5,"keypad"),
        keyChannel(this, "keyChannel"),
        plrID(0), wpnPwr(0),
        data(0), time(0),
        keyID('\0'),
        paramCtrl(paramCtrl),
        screen(screen)
    {}

void keypad::main(){
    hwlib::cout << "keypad\n";
    for(;;){
        hwlib::wait_ms(10);
        screen.write_message(3, 100);
        keyID = keypad_Matrix.getc();
        if(keyID == keyA){
            screen.write_message(4, 100);
            keyID = keypad_Matrix.getc();
            
            plrID = keyID - 48;
            
            screen.write_message(10, plrID);
            keyID = keypad_Matrix.getc();
            
            if(keyID != keySter){
                plrID = (plrID * 10) + keyID - 48;
                screen.write_message(10, keyID - 48);
                keyID = keypad_Matrix.getc();
            }
            if(plrID > 0 && plrID < 32 && keyID == keySter){
                screen.write_message(7, 100);
                screen.write_plrID(plrID);
                paramCtrl.set_plrID(plrID);
                continue;
            }
            else{
                screen.write_message(2, 100);
                screen.write_plrID(0);
                continue;
            }
        }
        
        else if(keyID == keyB){
            screen.write_message(5, 100);
            keyID = keypad_Matrix.getc();
            
            wpnPwr = keyID - 48;
            
            screen.write_message(10, wpnPwr);
            keyID = keypad_Matrix.getc();
            
            if(keyID != keySter){
                wpnPwr = (wpnPwr * 10) + keyID - 48;
                screen.write_message(10, keyID - 48);
                keyID = keypad_Matrix.getc();
            }
            if(wpnPwr >= 0 && wpnPwr < 32 && keyID == keySter){
                screen.write_message(8, 100);
                screen.write_wpnPwrID(wpnPwr);
                paramCtrl.set_wpnPwr(wpnPwr);
            }
            else{
                screen.write_message(2, 100);
                screen.write_wpnPwrID(32);
                continue;
            }
        }
        else if(keyID == keyC){
            screen.write_message(6, 100);
            keyID = keypad_Matrix.getc();
            
            data = keyID - 48;
            
            screen.write_message(10, data);
            keyID = keypad_Matrix.getc();
            
            if(keyID != keySter){
                data = (data * 10) + keyID - 48;
                screen.write_message(10, keyID - 48);
                keyID = keypad_Matrix.getc();
            }
            if(data > 0 && data < 32 && keyID == keySter){
                time = data;
                paramCtrl.sendMessage(time);
                screen.write_message(9, 100);
                screen.write_Min(time);
                screen.write_Sec(0);
            }
            else if(data == 0 && time > 0 && time < 32 && wpnPwr >= 0 && wpnPwr < 32 && plrID > 0 && plrID < 32 && keyID == keySter){
                paramCtrl.sendMessage(data);
                screen.write_message(1, 100);
            }
            else{
                time = 0;
                screen.write_message(2, 100);
                screen.write_Min(0);
                screen.write_Sec(0);
                continue;
            }
        }  
        else{
            screen.write_message(2, 100);
        }
    } 
}
