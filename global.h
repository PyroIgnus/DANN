#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>

extern FILE *file;

extern int CUE_SEED;
extern int NUM_RESERVOIRS;
extern int NUM_SENSORS;
extern int NUM_MOTORS;
extern int MAX_AXON_LENGTH;
extern int MAX_SYNAPSES;
extern int MAX_WEIGHT;
extern int MAX_CUE;
extern int SEARCH_RADIUS;

extern int ACTION_POTENTIAL;
extern int THRESHOLD;
extern int RECOVERY_PERIOD;
extern int RECOVERY_THRESHOLD;
extern int INITIAL_SYNAPSE_WEIGHT;
extern float CUE_CHANGE;
extern float WEIGHT_CHANGE;
extern float LIFESPAN_INCREASE;
extern float LIFESPAN_DECREASE;

extern int numNeurons;

#endif // GLOBAL_H
