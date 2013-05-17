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

Synapse::~Synapse()
{
    //dtor
}
