#include "Synapse.h"

Synapse::Synapse()
{
    //ctor
}

Synapse::Synapse(Neuron* target) {
    this->target = target;
    weight = INITIAL_SYNAPSE_WEIGHT;
}

void Synapse::trigger(float value) {
    target->acceptSignal(value);
    // Increment weight/lifespan.
}

Neuron* Synapse::getTarget() {
    return target;
}

void Synapse::depreciate(float value) {
    // Decrease weight/lifespan by something related to the value (or something constant).
}

Synapse::~Synapse()
{
    //dtor
}
