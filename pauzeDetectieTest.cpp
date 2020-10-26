#include "hwlib.hpp" 
#include <iostream>
#include <vector>

int pauze_detectie(){
    int total_time, idle, signal = 0;
    
    for(;;){
        tsop_signal.refresh();
        if(total_time == 2400){
            if(1500 > signal < 1700 && 700 > idle < 900){
                return 1;
            }
            else if(700 > signal < 900 && 1500 > idle < 1700){
                return 0;
            }
        }
        if( tsop_signal.read() == 0 ){
            signal += 50;  
        }
        else if( tsop_signal.read() == 1 ){
            idle += 50;
        }
        total_time += 50;
        hwlib::wait_ms( 0.05 );
    }
}

int main(void){
    namespace target = hwlib::target;
   
    auto tsop_signal = target::pin_in( target::pins::d8 );
    auto tsop_gnd    = target::pin_out( target::pins::d9 );
    auto tsop_vdd    = target::pin_out( target::pins::d10 );
    tsop_gnd.write( 0 );
    tsop_vdd.write( 1 );
    tsop_gnd.flush();
    tsop_vdd.flush();
    
    int total_time, idle, signal, state = 0;
    vector<int> waarde;
    
    for(;;){
        tsop_signal.refresh();
        if( tsop_signal.read() == 0 ){
            state = 1; 
        }
        while(state == 1){
            tsop_signal.refresh();
            if(total_time == 13500){
                if(8900 > signal < 9100 && 4400 > idle < 4600){
                    for(int i = 0; i < 32; i++){
                        waarde.push_back(pauze_detectie());
                        cout << "bit nummer " << i << " is: " << pauze_detectie();
                        int total_time, idle, signal = 0;
                    }
                    state = 0;
                }
            }
            if( tsop_signal.read() == 0 ){
                signal += 50;  
            }
            else if( tsop_signal.read() == 1 ){
                idle += 50;
            }
            total_time += 50;
            hwlib::wait_ms( 0.05 );
        }
    }
}
