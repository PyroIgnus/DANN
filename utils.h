#ifndef	UTILS_H
#define UTILS_H

#include <stdio.h>

#define NUM_RESERVOIRS 1
#define MAX_RES_SIZE 5
#define NUM_SENSORS 5
#define NUM_MOTORS 5
#define MAX_INPUTS 1000
#define MAX_AXON_LENGTH 10
#define MAX_SYNAPSES 10000

#define THRESHOLD 50
#define RECOVERY_PERIOD 3
#define RECOVERY_THRESHOLD 150
#define INITIAL_SYNAPSE_WEIGHT 0.5
#define CUE_CHANGE 0.25
#define WEIGHT_CHANGE 0.1

#define LOGGING 1

void logger(FILE *file, char *message);

#endif
