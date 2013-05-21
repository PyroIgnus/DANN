#include "Synapse.h"

Synapse::Synapse()
{
    //ctor
}

Synapse::Synapse(Neuron* target, Neuron* origin) {
    this->target = target;
    weight = INITIAL_SYNAPSE_WEIGHT;
    next = NULL;
    this->origin = origin;

    // Add this connection to target.
    target->addConnection(origin);
}

void Synapse::trigger(float value) {
    target->acceptSignal(value, origin);
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

float Synapse::getWeight() {
    return weight;
}

Synapse::~Synapse()
{
    target->removeConnection(origin);
}

void Synapse::deleteAll() {
    if (next != NULL) {
        next->deleteAll();
    }
    delete this;
}
