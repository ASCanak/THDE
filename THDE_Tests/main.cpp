#include "hwlib.hpp" 

int pauze_detectie(unsigned int n){
	if( n > 300 && n < 1000)
		return 1;
	else if( n > 1000 && n < 3000)
		return 0;
	else
		return 2;
}

void ir_receiver(){
	namespace target = hwlib::target;
	
	auto tsop_signal = target::pin_in( target::pins::d8 );
	auto tsop_gnd    = target::pin_out( target::pins::d9 );
	auto tsop_vdd    = target::pin_out( target::pins::d10 );
	tsop_gnd.write( 0 );
	tsop_vdd.write( 1 );
	tsop_gnd.flush();
	tsop_vdd.flush();
	
	unsigned int idle, arrayCount = 0;
	unsigned int bitSize = 32;
	int array [bitSize];
	
	for(;;){
		tsop_signal.refresh();
		if(arrayCount == bitSize)
			break;	
		else if( tsop_signal.read() == 0 && idle > 0 && arrayCount != bitSize){
			if(pauze_detectie(idle) != 2){
				array[arrayCount] = pauze_detectie(idle);
				arrayCount++;
				idle = 0;
			}
			else if(pauze_detectie(idle) == 2)
				idle = 0;
			else 
				continue;
		}
		else
			idle += 100;
		hwlib::wait_us( 100 );
	}
	for(unsigned int i = 0; i < bitSize; i++){
		hwlib::cout << array[i] << " ";
	}
	hwlib::cout << "\n";
	return;
}

int main( void ){
	for(;;){
		ir_receiver();
	}
}