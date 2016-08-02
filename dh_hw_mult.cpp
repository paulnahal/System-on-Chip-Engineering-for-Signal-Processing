#include "systemc.h"
#include "digit.h"
#include "dh_hw_mult.h"

#include "modules.h"



void dh_hw_mult::process_hw_mult()
{
  NN_DIGIT a[2], b, c, t, u;
  //NN_HALF_DIGIT bHigh, bLow, cHigh, cLow;

    while (true)
    {
      if (reset.read() == true){
            state.write(S0_WAIT);
            hw_mult_done.write(false);
        }
      else
        {
          switch(state.read()){

            case S0_WAIT: // wait for enable signal to be asserted
                if (hw_mult_enable.read() == true) {
                  state.write(S1_EXECUTE);
                }
                break;

            case S1_EXECUTE: //multiply the inputs
                // Read inputs  
                /*b = in_data_1.read();
                c = in_data_2.read();*/

                // Original code from NN_DigitMult()... 
                /*bHigh = b_high.read(); //(NN_HALF_DIGIT)HIGH_HALF (b);
                bLow = b_low.read(); //(NN_HALF_DIGIT)LOW_HALF (b);
                cHigh = c_high.read();//(NN_HALF_DIGIT)HIGH_HALF (c);
                cLow = c_low.read(); //(NN_HALF_DIGIT)LOW_HALF (c);*/

                a[0] = a0temp.read();//(NN_DIGIT)bLow * (NN_DIGIT)cLow;
                t = t_temp.read(); //(NN_DIGIT)bLow * (NN_DIGIT)cHigh;
                u = u_temp.read(); //(NN_DIGIT)bHigh * (NN_DIGIT)cLow;
                a[1] = a1temp.read();//(NN_DIGIT)bHigh * (NN_DIGIT)cHigh;
              
                if ((t += u) < u) a[1] += TO_HIGH_HALF (1); //t = t + u < u
                u = TO_HIGH_HALF (t);
              
                if ((a[0] += u) < u) a[1]++;
                a[1] += HIGH_HALF (t);

                state.write(S2_OUTPUT);
              break;

            case S2_OUTPUT: //write to modules output ports, assert done signal

                // Write Outputs
                out_data_low.write(a[0]);
                out_data_high.write(a[1]);

                hw_mult_done.write(true);
                wait();
                
                state.write(S3_FINISH);
              break;

            case S3_FINISH: //check if enable is deasserted, if so deassert done
                if (hw_mult_enable.read() == false)
                    {
                        hw_mult_done.write(false);
                        wait();
                        state.write(S0_WAIT);
                    }
              break;
            }
          }wait();
        } 
      }



  /*
  NN_DIGIT a[2], b, c, t, u;
  NN_HALF_DIGIT bHigh, bLow, cHigh, cLow;

  for (;;) {  
  
    if (hw_mult_enable.read() == true) 
    {	

	// Read inputs	
	b = in_data_1.read();
	c = in_data_2.read();
		
	// Original code from NN_DigitMult()...		
  	bHigh = (NN_HALF_DIGIT)HIGH_HALF (b);
  	bLow = (NN_HALF_DIGIT)LOW_HALF (b);
  	cHigh = (NN_HALF_DIGIT)HIGH_HALF (c);
  	cLow = (NN_HALF_DIGIT)LOW_HALF (c);

  	a[0] = (NN_DIGIT)bLow * (NN_DIGIT)cLow;
  	t = (NN_DIGIT)bLow * (NN_DIGIT)cHigh;
  	u = (NN_DIGIT)bHigh * (NN_DIGIT)cLow;
  	a[1] = (NN_DIGIT)bHigh * (NN_DIGIT)cHigh;
  
  	if ((t += u) < u) a[1] += TO_HIGH_HALF (1);
  	u = TO_HIGH_HALF (t);
  
  	if ((a[0] += u) < u) a[1]++;
  	a[1] += HIGH_HALF (t);
		
 	// Hardware multiplication delay = 100 ns
	wait (100, SC_NS);
	
	// Write outputs
	out_data_low.write(a[0]);
	out_data_high.write(a[1]);
		
    }

    wait();		// wait for a change of hw_mult_enable	

  }*/

