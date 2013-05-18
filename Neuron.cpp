#include "Neuron.h"
#include <stdio.h>

Neuron::Neuron()
{
    logger (file, "Neuron Created.\n");
    position[0] = -1;
    position[1] = -1;
    position[2] = -1;
    alive = true;
    cue = 0;  // "Random" cue value for unspecified cues.
    for (int i = 0; i < MAX_INPUTS; i++) {
        dendrites[i] = 0;
    }
    threshold = THRESHOLD;
    recoveryPeriod = RECOVERY_PERIOD;
    recoveryThreshold = RECOVERY_THRESHOLD;
    axon = new Axon(-1, -1, -1);
}

Neuron::Neuron(int x, int y, int z) {

    logger (file, "Neuron Created.\n");
    position[0] = x;
    position[1] = y;
    position[2] = z;
    alive = true;
    cue = (x + y + z) % 2;  // "Random" cue value for unspecified cues.
    for (int i = 0; i < MAX_INPUTS; i++) {
        dendrites[i] = 0;
    }
    threshold = THRESHOLD;
    recoveryPeriod = RECOVERY_PERIOD;
    recoveryThreshold = RECOVERY_THRESHOLD;
    axon = new Axon(x, y, z);

}

Neuron::Neuron(int x, int y, int z, float cue) {

    logger (file, "Neuron Created.\n");
    position[0] = x;
    position[1] = y;
    position[2] = z;
    alive = true;
    this->cue = cue;
    for (int i = 0; i < MAX_INPUTS; i++) {
        dendrites[i] = 0;
    }
    threshold = THRESHOLD;
    recoveryPeriod = RECOVERY_PERIOD;
    recoveryThreshold = RECOVERY_THRESHOLD;
    axon = new Axon(x, y, z, cue);
}

void Neuron::acceptSignal(float value) {
    // Append this value to the array of values to be processed.
}

float Neuron::process() {
    // Process the queued input values from the dendrites and return that value.
    float result = 0;

    return result;
}

void Neuron::activatePotential(float value) {
    // If the value exceeds the threshold, then pass value into axon (passSignal()).
}

bool Neuron::equals(Neuron* other) {
    if (position[0] == other->getX()) {
        if (position[1] == other->getY()) {
            if (position[2] == other->getZ()) {
                return true;
            }
        }
    }
    return false;
}

int Neuron::getX() {
    return position[0];
}

int Neuron::getY() {
    return position[1];
}

int Neuron::getZ() {
    return position[2];
}

Axon* Neuron::getAxon() {
    return axon;
}

Neuron::~Neuron()
{
    delete axon;
    logger (file, "Neuron Destroyed.\n");
}
