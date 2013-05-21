#include "NeuralNetwork.h"
#include <queue>
#include <list>

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

void NeuralNetwork::linkSensor(Neuron* sensor, Neuron* target) {
    // Link the sensor Neuron to target Neuron by means of axon and synapses.
    sensor->getAxon()->forceLink(target);
}

void NeuralNetwork::linkMotor(Neuron* target, Neuron* motor) {
    // Link the target Neuron to motor Neuron by means of axon and synapses.
    target->getAxon()->forceLink(motor);
}

void NeuralNetwork::train() {
    // Method to train.  Probably specific to what the DANN is being trained for.
    updateSensors();
    process();
    // use cueEvolveBackPropagation() to update cues.
}

void NeuralNetwork::updateSensors() {
    // Update sensor Neuron dendrite values.  Specific to each Sensor.

}

void NeuralNetwork::process() {
    // Commence a breadth first signal pass starting from the sensor Neurons.
    std::queue<Neuron*> unprocessed;
    std::list<Neuron*> processed;
    Neuron* current;
    Neuron* check;
    Synapse* head;
    Synapse* curr;
    bool isUnique;

    for (int i = 0; i < numSensors; i++) {
        unprocessed.push(sensors[i]);
    }

    while (!unprocessed.empty()) {

        // Process the next Neuron.
        current = unprocessed.front();
        head = current->getAxon()->getSynapseHead();
        curr = head;
        // Add new Neurons to the queue if necessary
        isUnique = true;
        for (int i = 0; i < current->getAxon()->getNumSynapses(); i++) {
            check = curr->getTarget();
            // Check for duplicates before pushing new Neurons into the queue.
            for (std::list<Neuron*>::iterator it = processed.begin(); it != processed.end(); it++) {
                if ((*it)->equals(check)) {
                    it = processed.end();
                    isUnique = false;
                }
            }
            if (isUnique) {
                unprocessed.push(check);
            }
            curr = curr->getNext();
        }
        // Send an action potential if necessary.
        current->activatePotential(current->process());
        // Remove Neuron as it has just been processed.
        unprocessed.pop();

    }

    // Decrease the lifespan of all Synapses.
    for (int res = 0; res < numReservoirs; res++) {
        for (int i = 0; i < resDimension; i++) {
            for (int j = 0; j < resDimension; j++) {
                for (int k = 0; k < resDimension; k++) {
                    current = reservoir[res]->getNeuron(i, j, k);
                    head = current->getAxon()->getSynapseHead();
                    curr = head;
                    for (int i = 0; i < current->getAxon()->getNumSynapses(); i++) {
                        curr->depreciate(0.1);
                        curr = curr->getNext();
                    }
                }
            }
        }
    }
}

void NeuralNetwork::updateCues(Neuron* motor, bool reinforce) {
    // Back propagate starting from the target motor Neuron and change cues accordingly.
    // Commence a backward breadth first search starting from the motor Neuron.
    std::queue<Neuron*> unprocessed;
    std::list<Neuron*> processed;
    Neuron* current;
    Neuron* check;
    bool isUnique;
    float change = CUE_CHANGE;
    if (!reinforce) {
        change = change * (-1);
    }

    unprocessed.push(motor);

    while (!unprocessed.empty()) {

        // Process the next Neuron.
        current = unprocessed.front();
        // Add new Neurons to the queue if necessary
        isUnique = true;
        for (int i = 0; i < current->getConnSize(); i++) {
            check = current->getConnection(i);
            // Check for duplicates before pushing new Neurons into the queue.
            for (std::list<Neuron*>::iterator it = processed.begin(); it != processed.end(); it++) {
                if ((*it)->equals(check)) {
                    it = processed.end();
                    isUnique = false;
                }
            }
            if (isUnique) {
                unprocessed.push(check);
            }
        }
        // Send an action potential if necessary.
        current->changeCue(change);
        // Remove Neuron as it has just been processed.
        unprocessed.pop();

    }
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

