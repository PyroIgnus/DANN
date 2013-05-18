#include "Axon.h"
#include <stdio.h>

Axon::Axon()
{
    logger (file, "Axon created.\n");
}

Axon::Axon(int x, int y, int z)
{
    logger (file, "Axon created.\n");

    maxSynapses = MAX_SYNAPSES;
    maxAxonLength = MAX_AXON_LENGTH;

    position[0][0] = x;
    position[0][1] = y;
    position[0][2] = z;
    cue = (x + y + z) % 2;  // "Random" cue value for unspecified cues.
    direction[0] = 0;
    direction[1] = 0;
    direction[2] = 0;
    numSynapses = 0;
    for (int i = 0; i < maxSynapses; i++) {
        synapse[i] = NULL;
    }
}

Axon::Axon(int x, int y, int z, float cue)
{
    logger (file, "Axon created.\n");

    maxSynapses = MAX_SYNAPSES;
    maxAxonLength = MAX_AXON_LENGTH;

    position[0][0] = x;
    position[0][1] = y;
    position[0][2] = z;
    this->cue = cue;
    direction[0] = 0;
    direction[1] = 0;
    direction[2] = 0;
    numSynapses = 0;
    for (int i = 0; i < maxSynapses; i++) {
        synapse[i] = NULL;
    }
}

void Axon::setDirection() {
    // Use the axon's position to determine which Neurons to check.  Might need a way to have access to the Reservoir's Neuron array.
}

void Axon::growDirection() {
    // Use the direction to find and snap to a new location.
}

void Axon::createSynapses() {
    // Create Synapses to add to the array and link them to the nearby Neurons.  Might need a way to have access to the Reservoir's Neuron array.
}

void Axon::createSynapse(Neuron* target) {
    // Create a Synapse with the specified target.
}

void Axon::removeSynpase() {
    // Check the array for any Synapses that need removing (below threshold).
}

void Axon::passSignal(float value) {
    // Iterates through the array of synapses and calls their trigger().
    int temp = numSynapses;
    for (int i = 0; i < temp; i++) {
        if (synapse[i] == NULL) {
            temp += 1;
        }
        else {
            synapse[i]->trigger(value);
        }
    }
}

Synapse* Axon::getSynapse(int index) {
    return synapse[index];
}

int Axon::getNumSynapses() {
    return numSynapses;
}

Axon::~Axon()
{
    for (int i = 0; i < maxSynapses; i++) {
        if (synapse[i] != NULL) {
            delete synapse[i];
        }
    }
    logger (file, "Axon destroyed.\n");
}
