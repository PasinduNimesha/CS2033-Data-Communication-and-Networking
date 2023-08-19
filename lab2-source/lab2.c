// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()

// user-defined header files
#include "mypcm.h"


// function prototypes
void run(asignal * inputsignal, float interval);


int main()
{
    asignal * inputsignal = (asignal *) malloc(sizeof(asignal));
    float interval;
    
    scanf("%f %f %f %d %f", &inputsignal->A, &inputsignal->omega, &inputsignal->sigma, &inputsignal->duration, &interval);
    run(inputsignal, interval);
    
    //call any other function here

    free(inputsignal);
	return 0;
}

void run(asignal * inputsignal, float interval) 
{
    float samples[100];
	sampler(samples, interval, * inputsignal);
    for(int i = 0; i < 10; i++){
        printf("%d : %f \n", i, samples[i]);
    }
}


