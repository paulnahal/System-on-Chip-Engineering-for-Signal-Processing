#include "systemc.h"
#include "digit.h"
#include "dh_sw.h"
#include "dh_hw_mult.h"
#include "modules.h"

int sc_main(int argc , char *argv[])
{

	sc_signal <bool> reset, enable, done;
	sc_signal <NN_DIGIT> operand1, operand2, result1, result2;
	//newtest
	sc_signal <NN_DIGIT> b_high, c_high, b_low, c_low; //highlow
	sc_signal<NN_DIGIT> a0temp, t_temp, u_temp, a1temp; // multiplication
	sc_clock TestClk ("TestClock", 10, SC_NS, 0.5);
	
	enable.write(false);
	done.write(false);
	reset.write(false);
	
	dh_sw DH_SW("DH_Software");
	DH_SW.out_data_1 (operand1);		// operand1 to hardware
	DH_SW.out_data_2 (operand2);		// operand2 to hardware
	DH_SW.in_data_low (result1);		// result1 from hardware
	DH_SW.in_data_high (result2);		// result2 from hardware
	DH_SW.hw_mult_enable (enable);		// enable hardware
	DH_SW.hw_mult_done (done);		// hardware done
	
	
	dh_hw_mult DH_HW_MULT("DH_Hardware_Multiplier");
	DH_HW_MULT.in_data_1 (operand1);	// operand1 from software
	DH_HW_MULT.in_data_2 (operand2);	// operand2 from software
	DH_HW_MULT.out_data_low (result1);	// result1 to software
	DH_HW_MULT.out_data_high (result2);	// result2 to software
	DH_HW_MULT.hw_mult_enable (enable);	// enable hardware
	DH_HW_MULT.hw_mult_done (done);		// hardware done
	DH_HW_MULT.reset(reset);
	DH_HW_MULT.clock (TestClk);
	//newtest
	DH_HW_MULT.b_high(b_high);
	DH_HW_MULT.c_high(c_high);
	DH_HW_MULT.b_low(b_low);
	DH_HW_MULT.c_low(c_low);
	DH_HW_MULT.a0temp(a0temp);
	DH_HW_MULT.t_temp(t_temp);
	DH_HW_MULT.u_temp(u_temp);
	DH_HW_MULT.a1temp(a1temp);


	//newtest
	hhalf H_HALF1("high_half_maker_b");
	H_HALF1.IN(operand1);
	H_HALF1.OUT(b_high);
	hhalf H_HALF2("high_half_maker_c");
	H_HALF2.IN(operand2);
	H_HALF2.OUT(c_high);
	lhalf L_HALF1("low_half_maker_b");
	L_HALF1.IN(operand1);
	L_HALF1.OUT(b_low);
	lhalf L_HALF2("low_half_maker_c");
	L_HALF2.IN(operand2);
	L_HALF2.OUT(c_low);

	mult MULT1("Multiply_a0");
	MULT1.A(b_low);
	MULT1.B(c_low);
	MULT1.OUT(a0temp);
	mult MULT2("Multiply_t");
	MULT2.A(b_low);
	MULT2.B(c_high);
	MULT2.OUT(t_temp);
	mult MULT3("Multiply_u");
	MULT3.A(b_high);
	MULT3.B(c_low);
	MULT3.OUT(u_temp);
	mult MULT4("Multiply_a1");
	MULT4.A(b_high);
	MULT4.B(c_high);
	MULT4.OUT(a1temp);


	sc_start();

	return(0);
}
