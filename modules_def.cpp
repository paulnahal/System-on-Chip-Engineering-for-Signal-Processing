/*
function definitions for modules.h
*/

#include "systemc.h"
#include "modules.h"
#include "digit.h"

void hhalf::hhalf_process(){
	OUT.write((IN.read() >> NN_HALF_DIGIT_BITS) & MAX_NN_HALF_DIGIT);
}
void lhalf::lhalf_process(){
	OUT.write(IN.read() & MAX_NN_HALF_DIGIT);
}

void mult::mult_process() {
    
	OUT.write(A.read()*B.read());
    
}

void add::add_process() {
    
    OUT.write(A.read() + B.read());
}

void comp::comp_process() {
    
    if(A.read() < B.read())
    	OUT.write(1);
    	else
    	OUT.write(0);

}