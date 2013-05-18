#include "Synapse.h"

Synapse::Synapse()
{
    //ctor
}

Synapse::Synapse(Neuron* target) {
    this->target = target;
    weight = INITIAL_SYNAPSE_WEIGHT;
    next = NULL;
}

void Synapse::trigger(float value) {
    target->acceptSignal(value);
    // Increment weight/lifespan.
}

Neuron* Synapse::getTarget() {
    return target;
}

void Synapse::setTarget(Neuron* target) {
    this->target = target;
}

Synapse* Synapse::getNext() {
    return next;
}

void Synapse::setNext(Synapse* next) {
    this->next = next;
}

void Synapse::depreciate(float value) {
    // Decrease weight/lifespan by something related to the value (or something constant).
}

Synapse::~Synapse()
{
    delete next;
}
