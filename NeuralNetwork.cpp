#include "NeuralNetwork.h"

// Default Constructor
NeuralNetwork::NeuralNetwork()
{
    logger (file, "Creating Neural Network.\n");
    numReservoirs = NUM_RESERVOIRS;
    resDimension = MAX_RES_SIZE;
    numSensors = NUM_SENSORS;
    numMotors = NUM_MOTORS;
    maxInputs = MAX_INPUTS;
    maxAxonLength = MAX_AXON_LENGTH;
    maxSynapses = MAX_SYNAPSES;

    criticalPeriod = false;
    sensitivityPeriod = false;

    for (int i = 0; i < numSensors; i++) {
        sensors[i] = new Neuron();
    }
    for (int i = 0; i < numReservoirs; i++) {
        reservoir[i] = new Reservoir(resDimension);
    }
    for (int i = 0; i < numMotors; i++) {
        motors[i] = new Neuron();
    }
    logger (file, "Neural Network Successfully Created.\n");
}

NeuralNetwork::NeuralNetwork(char* filename)
{


}

void NeuralNetwork::train() {
    // Method to train.
}

void NeuralNetwork::updateSensors() {
    // Update sensor Neuron dendrite values.
}

void NeuralNetwork::process() {
    // Commence a breadth first signal pass starting from the sensor Neurons.

    // Decrease the lifespan of all Synapses.
}

void NeuralNetwork::determineState() {
    // Check output and apply consequences (change critical/sensitivityPeriods).
}

NeuralNetwork::~NeuralNetwork()
{
    logger (file, "Destroying Neural Network.\n");
    for (int i = 0; i < numSensors; i++) {
        delete sensors[i];
    }
    for (int i = 0; i < numReservoirs; i++) {
        delete reservoir[i];
    }
    for (int i = 0; i < numMotors; i++) {
        delete motors[i];
    }
    logger (file, "Neural Network Successfully destroyed.\n");
}

