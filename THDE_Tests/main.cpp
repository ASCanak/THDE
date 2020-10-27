#include "hwlib.hpp" 

int pauze_detectie(unsigned int n){
	if( n > 300 && n < 1000)
		return 1;
	else if( n > 1000 && n < 3000)
		return 0;
	else
		return 2;
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
	
	int idle = 0;
	
	for(;;){
		tsop_signal.refresh();
			
		if( tsop_signal.read() == 0 && idle > 0 ){
			if(pauze_detectie(idle) != 2){
				
				hwlib::cout << "bit nummer is: " << pauze_detectie(idle) << '\n';
				idle = 0;
			}
			else if(pauze_detectie(idle) == 2){
				hwlib::cout << idle;
				idle = 0;
				hwlib::cout << " bit nummer is: " << pauze_detectie(idle) << '\n';
			}
			else 
				continue;
		}
		else{
			idle += 100;
			hwlib::cout << idle << '\n';
		}			
		hwlib::now_us();
		hwlib::wait_ms( 0.1 );
	}
}