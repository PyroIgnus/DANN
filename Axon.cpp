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
    direction[0] = 0;
    direction[1] = 0;
    direction[2] = 0;
    numSynapses = 0;
    head = NULL;
    tail = NULL;
//    for (int i = 0; i < maxSynapses; i++) {
//        synapse[i] = NULL;
//    }
}

Axon::Axon(int x, int y, int z, float cue)
{
    logger (file, "Axon created.\n");

    maxSynapses = MAX_SYNAPSES;
    maxAxonLength = MAX_AXON_LENGTH;

    position[0][0] = x;
    position[0][1] = y;
    position[0][2] = z;
    direction[0] = 0;
    direction[1] = 0;
    direction[2] = 0;
    numSynapses = 0;
    head = NULL;
    tail = NULL;
//    for (int i = 0; i < maxSynapses; i++) {
//        synapse[i] = NULL;
//    }
}

void Axon::setDirection() {
    // Use the axon's position to determine which Neurons to check.  Might need a way to have access to the Reservoir's Neuron array.
}

void Axon::growDirection() {
    // Use the direction to find and snap to a new location.
}

void Axon::forceLink(Neuron* target) {
    // Force create a Synapse to the target Neuron.
}

void Axon::createSynapses() {
    // Create Synapses to add to the list and link them to the nearby Neurons.  Might need a way to have access to the Reservoir's Neuron array.
}

void Axon::retractSynapses() {
   // Check the list for any Synapses that need removing (below threshold).
}

void Axon::removeSynapse(Synapse* target) {
    // Remove the Synapse from the linked list.
    Synapse* curr = head;
    Synapse* prev = head;
    if (head == target) {
        head = head->getNext();
        delete prev;
        numSynapses -= 1;
        return;
    }
    curr = head->getNext();
    while (curr) {
        if (curr == target) {
            if (curr == tail) {
                if (curr->getNext() == NULL) {
                    tail = prev;
                }
                else {
                    tail = curr->getNext();
                }
            }
            prev->setNext(curr->getNext());
            delete curr;
            numSynapses -= 1;
        }
        prev = curr;
        curr = curr->getNext();
    }
    return;
}

void Axon::insertSynapse(Synapse* target) {
    // Insert the Synapse into the linked list.
    if (numSynapses == 0) {
        head = target;
        tail = target;
        numSynapses = 1;
        return;
    }
    tail->setNext(target);
    tail = target;
    numSynapses += 1;
    return;
}

void Axon::passSignal(float value) {
    // Iterates through the array of synapses and calls their trigger().
    Synapse* curr = head;
    while (curr) {
        curr->trigger(value);
    }
//    int temp = numSynapses;
//    for (int i = 0; i < temp; i++) {
//        if (synapse[i] == NULL) {
//            temp += 1;
//        }
//        else {
//            synapse[i]->trigger(value);
//        }
//    }
}

Synapse* Axon::getSynapseHead() {
    return head;
}

int Axon::getNumSynapses() {
    return numSynapses;
}

Axon::~Axon()
{
    delete head;
//    for (int i = 0; i < maxSynapses; i++) {
//        if (synapse[i] != NULL) {
//            delete synapse[i];
//        }
//    }
    logger (file, "Axon destroyed.\n");
}
