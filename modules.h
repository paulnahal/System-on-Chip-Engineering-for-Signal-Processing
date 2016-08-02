/*
modules.h - modules for hardware multiplication
*/

#ifndef MODULES_H
#define MODULES_H
#include "systemc.h"
#include "digit.h"

//HIGH_HALF AND LOW_HALF MACROS
SC_MODULE(hhalf) {
    // Ports
    sc_in <NN_DIGIT> IN;
    sc_out <NN_DIGIT> OUT;

    void hhalf_process();
    
    SC_CTOR(hhalf) {
        SC_METHOD(hhalf_process);
        sensitive << IN;
    }
};
SC_MODULE(lhalf) {
    // Ports
    sc_in <NN_DIGIT> IN;
    sc_out <NN_DIGIT> OUT;

    void lhalf_process();
    
    SC_CTOR(lhalf) {
        SC_METHOD(lhalf_process);
        sensitive << IN;
    }
};

//MULTIPLY
SC_MODULE(mult) {
    //
    // Ports
    //
    sc_in<NN_DIGIT> A, B; 
    sc_out<NN_DIGIT> OUT;

    void mult_process();
    
    SC_CTOR(mult) {
        SC_METHOD(mult_process);
        sensitive << A << B;
    }
};

//ADD - Modified from sub in gcd_moore example
SC_MODULE(add) {
    // Ports
    sc_in <NN_DIGIT> A;
    sc_in <NN_DIGIT> B;	
    sc_out <NN_DIGIT> OUT;

    void add_process();
    
    SC_CTOR(add) {
        SC_METHOD(add_process);
        sensitive << A << B;
    }
};

// comp - comparator (modified from gcd_moore example)
SC_MODULE(comp) {
    // Ports
    sc_in <NN_DIGIT> A, B; 
    sc_out<NN_DIGIT> OUT;

    void comp_process();
    
    SC_CTOR(comp) {
        SC_METHOD(comp_process);
        sensitive << A << B;
    }
};





#endif