#include "hwlib.hpp" 
#include <vector>

int pauze_detectie(int n){
	if( n > 600 && n < 1000)
		return 1;
	else if( n > 1400 && n < 1800)
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
	vector<int> waarde;
	
	for(;;){
		tsop_signal.refresh();
			
		if( tsop_signal.read() == 0 && idle > 0 ){
			if(pauze_detectie(idle) != 2){
				waarde.push_back(pauze_detectie(idle));
				hwlib::cout << "bit nummer is: " << pauze_detectie(idle);
				idle = 0;
			}
			else 
				continue;
		}
		else
			idle += 100;
			
		hwlib::wait_ms( 0.1 );
	}
}
