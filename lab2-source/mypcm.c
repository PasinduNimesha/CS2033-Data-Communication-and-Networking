// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
#include <math.h>
//Add any necessary headers here

// user-defined header files
#include "mypcm.h" // do not modify this file

// put your function prototypes for additional helper functions below:


// implementation
float analog_signal_generator(asignal signal, int t)
{
	double angle;
	angle = (signal.omega * t) + signal.sigma;
	float x_t = signal.A*sin(angle);
	
	return x_t;
}
void sampler(float *samples, int interval, asignal signal)
{
	float value;
	int number_of_sample = signal.duration/interval;
	for(int i = 0; i < number_of_sample; i++){
		// printf("%f \n", analog_signal_generator(signal, i*interval));
		value = analog_signal_generator(signal, i*interval);
		samples[i] = value;
	}
}
void quantizer(float *samples, int *pcmpulses, int levels)
{
	//TODO
}
void encoder(int *pcmpulses, int *dsignal, int encoderbits)
{
	//TODO
}