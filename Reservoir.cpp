#include "Reservoir.h"

Reservoir::Reservoir()
{

    logger (file, "Reservoir Created.\n");

}

Reservoir::Reservoir(int resDimension)
{

    resSize = resDimension;
    logger (file, "Creating Reservoir.\n");
    for (int i = 0; i < resSize; i++) {
        for (int j = 0; j < resSize; j++) {
            for (int k = 0; k < resSize; k++) {
                neurons[i][j][k] = new Neuron(i, j, k, 1, this);
            }
        }
    }
    for (int i = 0; i < resSize; i++) {
        for (int j = 0; j < resSize; j++) {
            for (int k = 0; k < resSize; k++) {
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

Reservoir::~Reservoir()
{
    logger (file, "Destroying Reservoir.\n");
    for (int i = 0; i < resSize; i++) {
        for (int j = 0; j < resSize; j++) {
            for (int k = 0; k < resSize; k++) {
                delete neurons[i][j][k]->getAxon();
            }
        }
    }
    for (int i = 0; i < resSize; i++) {
        for (int j = 0; j < resSize; j++) {
            for (int k = 0; k < resSize; k++) {
                delete neurons[i][j][k];
            }
        }
    }
    logger (file, "Reservoir Successfully Destroyed.\n");
}
