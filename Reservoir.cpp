#include "Reservoir.h"
#include <stdlib.h>

Reservoir::Reservoir()
{

    logger (file, "Reservoir Created.\n");

}

Reservoir::Reservoir(int resDimension)
{
    float cue;
    srand(CUE_SEED);
    resSize[0] = resDimension;
    resSize[1] = resDimension;
    resSize[2] = resDimension;
    logger (file, "Creating Reservoir.\n");
    neurons.resize(resSize[0]);
    for (int i = 0; i < resSize[0]; i++) {
        neurons[i].resize(resSize[1]);
        for (int j = 0; j < resSize[1]; j++) {
            neurons[i][j].resize(resSize[2]);
            for (int k = 0; k < resSize[2]; k++) {
                cue = (float)rand()/((float)RAND_MAX/2) - 1;    // A random float value between -1 and 1.
                neurons[i][j][k] = new Neuron(i, j, k, cue, this);
            }
        }
    }
    for (int i = 0; i < resSize[0]; i++) {
        for (int j = 0; j < resSize[1]; j++) {
            for (int k = 0; k < resSize[2]; k++) {
                neurons[i][j][k]->getAxon()->setDirection();
                neurons[i][j][k]->getAxon()->growDirection();
            }
        }
    }
    logger (file, "Reservoir Successfully Created.\n");
}

Reservoir::Reservoir(int x, int y, int z)
{
    float cue;
    srand(CUE_SEED);
    resSize[0] = x;
    resSize[1] = y;
    resSize[2] = z;
    logger (file, "Creating Reservoir.\n");
    neurons.resize(resSize[0]);
    for (int i = 0; i < resSize[0]; i++) {
        neurons[i].resize(resSize[1]);
        for (int j = 0; j < resSize[1]; j++) {
            neurons[i][j].resize(resSize[2]);
            for (int k = 0; k < resSize[2]; k++) {
                cue = (float)rand()/((float)RAND_MAX/2) - 1;    // A random float value between -1 and 1.
                neurons[i][j][k] = new Neuron(i, j, k, cue, this);
                numNeurons += 1;
            }
        }
    }
    for (int i = 0; i < resSize[0]; i++) {
        for (int j = 0; j < resSize[1]; j++) {
            for (int k = 0; k < resSize[2]; k++) {
                neurons[i][j][k]->getAxon()->setDirection();
                neurons[i][j][k]->getAxon()->growDirection();
            }
        }
    }
    logger (file, "Reservoir Successfully Created.\n");
}

Neuron* Reservoir::getNeuron (int x, int y, int z) {
    return neurons[x][y][z];
}

int Reservoir::getResDim (int dim) {
    int resDim = resSize[dim];
    return resDim;
}

Reservoir::~Reservoir()
{
    logger (file, "Destroying Reservoir.\n");
    for (int i = 0; i < resSize[0]; i++) {
        for (int j = 0; j < resSize[1]; j++) {
            for (int k = 0; k < resSize[2]; k++) {
                delete neurons[i][j][k]->getAxon();
            }
        }
    }
    for (int i = 0; i < resSize[0]; i++) {
        for (int j = 0; j < resSize[1]; j++) {
            for (int k = 0; k < resSize[2]; k++) {
                delete neurons[i][j][k];
            }
        }
    }
    logger (file, "Reservoir Successfully Destroyed.\n");
}
