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
                neurons[i][j][k] = new Neuron(i, j, k);
            }
        }
    }
    logger (file, "Reservoir Successfully Created.\n");
}

void Reservoir::linkSensor(Neuron* sensor, Neuron* target) {
    // Link the sensor Neuron to target Neuron by means of axon and synapses.
}

void Reservoir::linkMotor(Neuron* target, Neuron* motor) {
    // Link the target Neuron to motor Neuron by means of axon and synapses.
}

Reservoir::~Reservoir()
{
    logger (file, "Destroying Reservoir.\n");
    for (int i = 0; i < resSize; i++) {
        for (int j = 0; j < resSize; j++) {
            for (int k = 0; k < resSize; k++) {
                delete neurons[i][j][k];
            }
        }
    }
    logger (file, "Reservoir Successfully Destroyed.\n");
}
