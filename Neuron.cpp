#include "Neuron.h"
#include <stdio.h>

Neuron::Neuron()
{
    logger (file, "Neuron Created.\n");
    position[0] = -10;
    position[1] = -10;
    position[2] = -10;
    alive = true;
    cue = 0;
    for (int i = 0; i < MAX_INPUTS; i++) {
        dendrites[i] = 0;
    }
    numDendritesActive = 0;
    threshold = THRESHOLD;
    recoveryPeriod = RECOVERY_PERIOD;
    recoveryThreshold = RECOVERY_THRESHOLD;
    axon = new Axon(-10, -10, -10, this);

    connection.resize(MAX_INPUTS);
    counter.resize(MAX_INPUTS);
    numConnections = 0;
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
    numDendritesActive = 0;
    threshold = THRESHOLD;
    recoveryPeriod = RECOVERY_PERIOD;
    recoveryThreshold = RECOVERY_THRESHOLD;
    axon = new Axon(x, y, z, this);

    connection.resize(MAX_INPUTS);
    counter.resize(MAX_INPUTS);
    numConnections = 0;
}

Neuron::Neuron(int x, int y, int z, float cue, Reservoir* res) {

    logger (file, "Neuron Created.\n");
    position[0] = x;
    position[1] = y;
    position[2] = z;
    alive = true;
    this->cue = cue;
    for (int i = 0; i < MAX_INPUTS; i++) {
        dendrites[i] = 0;
    }
    numDendritesActive = 0;
    threshold = THRESHOLD;
    recoveryPeriod = RECOVERY_PERIOD;
    recoveryThreshold = RECOVERY_THRESHOLD;
    axon = new Axon(x, y, z, this);
    this->res = res;

    connection.resize(MAX_INPUTS);
    counter.resize(MAX_INPUTS);
    numConnections = 0;
}

void Neuron::addConnection(Neuron* source) {
    // Check to see if this neuron needs to be added to the connection vector list.
    for (int i = 0; i < numConnections; i++) {
        if (source == connection[i]) {
            counter[i] += 1;
            return;
        }
    }
    // Since the neuron is unique, add it into the vector array.
    connection[numConnections] = source;
    counter[numConnections] = 1;
    numConnections += 1;
}

void Neuron::removeConnection(Neuron* source) {
    // Decreases counter and removes connection if counter reaches 0.
    std::vector<Neuron*>::iterator it1 = connection.begin();
    std::vector<int>::iterator it2 = counter.begin();
    for (int i = 0; i < numConnections; i++) {
        if (source == connection[i]) {
            counter[i] -= 1;
            if (counter[i] == 0) {
                connection.erase(it1 + i);
                counter.erase(it2 + i);
                connection.push_back(NULL);
                counter.push_back(0);
            }
        }
    }
}

void Neuron::acceptSignal(float value, Neuron* source) {
    // Append this value to the array of values to be processed.
    dendrites[numDendritesActive] = value;
    numDendritesActive += 1;
}

float Neuron::process() {
    // Process the queued input values from the dendrites and return that value.
    float result = 0;

    for (int i = 0; i < numDendritesActive; i++) {
        result += dendrites[i];
    }

    // Reset counter.
    numDendritesActive = 0;

    // Return result.
    return result;
}

void Neuron::activatePotential(float value) {
    // If the value exceeds the threshold, then pass value into axon (passSignal()).
}

void Neuron::changeCue(float value) {
    cue += value;
}

bool Neuron::equals(Neuron* other) {
//    if (position[0] == other->getX()) {
//        if (position[1] == other->getY()) {
//            if (position[2] == other->getZ()) {
//                return true;
//            }
//        }
//    }
    if (other == this){
        return true;
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

Neuron* Neuron::getConnection(int index) {
    return connection[index];
}

int Neuron::getConnSize() {
    return connection.size();
}

float Neuron::getCue() {
    return cue;
}

Neuron::~Neuron()
{
    delete axon;
    logger (file, "Neuron Destroyed.\n");
}
