#ifndef	UTILS_H
#define UTILS_H

#include <stdio.h>

#define MNIST_TRAIN_IMAGES "/MNIST/Itraining.txt"
#define MNIST_TRAIN_LABELS "/MNIST/labeltraining.txt"
#define MNIST_TEST_IMAGES "/MNIST/Itest.txt"
#define MNIST_TEST_LABELS "/MNIST/labeltest.txt"

#define NUM_RESERVOIRS 1
//#define CUE_SEED 0
#define MAX_RES_SIZE 28
#define NUM_SENSORS 784
#define NUM_MOTORS 10
#define MAX_INPUTS 1000
//#define MAX_AXON_LENGTH 2
//#define MAX_SYNAPSES 10000
//#define MAX_WEIGHT 1
//#define MAX_CUE 1
//#define SEARCH_RADIUS 1
//
//#define ACTION_POTENTIAL 25
//#define THRESHOLD 15
//#define RECOVERY_PERIOD 3
//#define RECOVERY_THRESHOLD 40
//#define INITIAL_SYNAPSE_WEIGHT 100
//#define CUE_CHANGE 0.125
//#define WEIGHT_CHANGE 0.125

#define LOGGING 0

static const char CONFIG_COMMENT_CHAR = '#';

void logger(FILE *file, char *message);
int read_config(char *config_file);
int process_config_line(char *line);
void readMNIST(char* image_file, char* label_file, int num, int*** images, int* labels);

#endif
