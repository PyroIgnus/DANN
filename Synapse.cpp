#include "Synapse.h"
#include <cmath>

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

Synapse::Synapse(float weight, Neuron* target, Neuron* origin) {
    this->target = target;
    this->weight = weight;
    next = NULL;
    this->origin = origin;

    // Add this connection to target.
    target->addConnection(origin);
}

void Synapse::trigger(float value) {
    target->acceptSignal(value, origin);
    // Increment weight/lifespan.  Use only when reinforcement of action is required.  Won't need this until the system is autonomous.
    //changeWeight(0.01);
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

// Might not use.
void Synapse::depreciate(float value) {
    // Decrease weight/lifespan by something related to the value (or something constant).
}

void Synapse::changeWeight(float value) {
    // Adds value to the weight.
    if (std::abs(weight + value) < MAX_WEIGHT) {
        weight += value;
    }
//    char buff[50];
//    sprintf(buff, "%lf ", weight);
//    logger(file, buff);
//    printf ("%lf ", weight);
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
