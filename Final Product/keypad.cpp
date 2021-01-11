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
        plrID(0), wpnPwr(0),
        data(0), time(0),
        keyID('\0'),
        paramCtrl(paramCtrl),
        screen(screen)
    {}

void keypad::main(){
    hwlib::cout << "keypad\n";
    for(;;){
        hwlib::cout << "Press A for plrID, B for wpnPwrID and C for the special commands: ";
        keyID = keypad_Matrix.getc();
        hwlib::cout << keyID << "\n";
        if(keyID == keyA){
            hwlib::cout << "enter plrID: ";
            keyID = keypad_Matrix.getc();
            hwlib::cout << keyID << "\n";
            plrID = keyID - 48;
            screen.write_plrID(plrID);
            hwlib::cout << "enter 2nd digit or press * to save current digit: ";
            keyID = keypad_Matrix.getc();
            hwlib::cout << keyID << "\n";
            
            if(keyID != keySter){
                plrID = (plrID * 10) + keyID - 48;
                hwlib::cout << plrID << "\n";
                keyID = keySter;
            }
            if(plrID > 0 && plrID < 32 && keyID == keySter){
                screen.write_plrID(plrID);
                paramCtrl.set_plrID(plrID);
                continue;
            }
            else{
                hwlib::cout << "invalid plrID\n";
                screen.write_plrID(0);
                continue;
            }
        }
        
        else if(keyID == keyB){
            hwlib::cout << "enter wpnPwrID: ";
            keyID = keypad_Matrix.getc();
            hwlib::cout << keyID << "\n";
            wpnPwr = keyID - 48;
            screen.write_wpnPwrID(wpnPwr);
            hwlib::cout << "enter 2nd digit or press * to save current digit: ";
            keyID = keypad_Matrix.getc();
            hwlib::cout << keyID << "\n";
            if(keyID != keySter){
                wpnPwr = (wpnPwr * 10) + keyID - 48;
                hwlib::cout << wpnPwr << "\n";
                keyID = keySter;
            }
            if(wpnPwr >= 0 && wpnPwr < 32 && keyID == keySter){
                screen.write_wpnPwrID(wpnPwr);
                paramCtrl.set_wpnPwr(wpnPwr);
            }
            else{
                hwlib::cout << "invalid wpnPwrID\n";
                screen.write_wpnPwrID(0);
                continue;
            }
        }
        else if(keyID == keyC){
            hwlib::cout << "enter data: ";
            keyID = keypad_Matrix.getc();
            hwlib::cout << keyID << "\n";
            data = keyID - 48;
            hwlib::cout << "enter 2nd digit or press * to save current digit: ";
            keyID = keypad_Matrix.getc();
            hwlib::cout << keyID << "\n";
            if(keyID != keySter){
                data = (data * 10) + keyID - 48;
                hwlib::cout << data << "\n";
                keyID = keySter;
            }
            if(data > 0 && data < 32 && keyID == keySter){
                time = data;
                paramCtrl.sendMessage(time);
                screen.write_Min(time);
                screen.write_Sec(0);
            }
            else if(data == 0 && time > 0 && time < 32 && wpnPwr >= 0 && wpnPwr < 32 && plrID > 0 && plrID < 32 && keyID == keySter){
                paramCtrl.sendMessage(data);
                screen.write_eventInfo(0,0,100,2);
            }
            else{
                hwlib::cout << "invalid data\n";
                screen.write_Min(0);
                screen.write_Sec(0);
                continue;
            }
        }  
    } 
}