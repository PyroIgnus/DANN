#ifndef	UTILS_H
#define UTILS_H

#include <stdio.h>

#define NUM_RESERVOIRS 1
#define MAX_RES_SIZE 3
#define NUM_SENSORS 2
#define NUM_MOTORS 1
#define MAX_INPUTS 1000
#define MAX_AXON_LENGTH 2
#define MAX_SYNAPSES 10000
#define MAX_WEIGHT 2
#define MAX_CUE 5
#define SEARCH_RADIUS 1

#define ACTION_POTENTIAL 25
#define THRESHOLD 50
#define RECOVERY_PERIOD 3
#define RECOVERY_THRESHOLD 40
#define INITIAL_SYNAPSE_WEIGHT 1
#define CUE_CHANGE 0.125
#define WEIGHT_CHANGE 0.125

#define LOGGING 0

void logger(FILE *file, char *message);

#endif
