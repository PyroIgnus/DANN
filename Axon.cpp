#include "Axon.h"
#include "Reservoir.h"
#include <stdio.h>
#include <math.h>

Axon::Axon()
{
//    logger (file, "Axon created.\n");
}

Axon::Axon(int x, int y, int z, Neuron* origin)
{
//    logger (file, "Axon created.\n");

    maxSynapses = MAX_SYNAPSES;
    maxAxonLength = MAX_AXON_LENGTH;

    position[0] = x;
    position[1] = y;
    position[2] = z;
    direction[0] = 0;
    direction[1] = 0;
    direction[2] = 0;
    numSynapses = 0;
    length = 0;
    head = NULL;
    tail = NULL;
    this->origin = origin;
    res = NULL;
//    for (int i = 0; i < maxSynapses; i++) {
//        synapse[i] = NULL;
//    }
}

Axon::Axon(int x, int y, int z, Neuron* origin, Reservoir* res)
{
//    logger (file, "Axon created.\n");

    maxSynapses = MAX_SYNAPSES;
    maxAxonLength = MAX_AXON_LENGTH;

    position[0] = x;
    position[1] = y;
    position[2] = z;
    direction[0] = 0;
    direction[1] = 0;
    direction[2] = 0;
    numSynapses = 0;
    length = 0;
    head = NULL;
    tail = NULL;
    this->origin = origin;
    this->res = res;
//    for (int i = 0; i < maxSynapses; i++) {
//        synapse[i] = NULL;
//    }
}

void Axon::setDirection() {
    float dirVec[] = {0, 0 ,0};
    direction[0] = 0;
    direction[1] = 0;
    direction[2] = 0;
    Reservoir* currRes;
    if (res == NULL) {
        if (origin->getConnection(0) != NULL)
            currRes = origin->getConnection(0)->getRes();
        else
            currRes = head->getTarget()->getRes();
    }
    else {
        currRes = res;
    }
    // Use the axon's position to determine which Neurons to check.
    for (int i = position[0] - SEARCH_RADIUS; i <= position[0] + SEARCH_RADIUS; i++) {
        if (i >= 0 && i < currRes->getResDim(0)) {
            for (int j = position[1] - SEARCH_RADIUS; j <= position[1] + SEARCH_RADIUS; j++) {
                if (j >= 0 && j < currRes->getResDim(1)) {
                    for (int k = position[2] - SEARCH_RADIUS; k <= position[2] + SEARCH_RADIUS; k++) {
                        if (k >= 0 && k < currRes->getResDim(2)) {
                            // Function of distance and cue.
                            dirVec[0] = position[0] - i;
                            dirVec[1] = position[1] - j;
                            dirVec[2] = position[2] - k;
                            if (currRes->getNeuron(i, j, k)->isAlive()) {
                                direction[0] += currRes->getNeuron(i, j, k)->getCue() / (dirVec[0] * dirVec[0]);
                                direction[1] += currRes->getNeuron(i, j, k)->getCue() / (dirVec[1] * dirVec[1]);
                                direction[2] += currRes->getNeuron(i, j, k)->getCue() / (dirVec[2] * dirVec[2]);
                            }
                        }
                    }
                }
            }
        }
    }
    // Normalize the direction vector.
    float magnitude = sqrt (pow (direction[0], 2) + pow (direction[1], 2) + pow (direction[2], 2));
    direction[0] = direction[0]/magnitude;
    direction[1] = direction[1]/magnitude;
    direction[2] = direction[2]/magnitude;
}

void Axon::growDirection() {
    // Use the direction to find and snap to a new location.  Watch for boundaries and max length.
    if (length < MAX_AXON_LENGTH) {
        if (position[0] + round (direction[0]) >= 0 && position[0] + round (direction[0]) < res->getResDim(0))
            position[0] += round (direction[0]);
        if (position[1] + round (direction[1]) >= 0 && position[1] + round (direction[1]) < res->getResDim(1))
            position[1] += round (direction[1]);
        if (position[2] + round (direction[2]) >= 0 && position[2] + round (direction[2]) < res->getResDim(2))
            position[2] += round (direction[2]);

//        if (round (direction[0]) > 0 || round (direction[1]) > 0 || round (direction[2]) > 0) {
            length += 1;
            // Create Synapses
            createSynapses();
            //printPosition();
//        }
    }
}

void Axon::forceLink(Neuron* target) {
    // Force create a Synapse to the target Neuron permanently.
    insertSynapse(new Synapse(target, origin));
}

void Axon::createSynapses() {
    // Create Synapses to add to the list and link them to the nearby Neurons.  Watch for boundaries.
    Reservoir* currRes;
    if (res == NULL) {
        if (origin->getConnection(0) != NULL)
            currRes = origin->getConnection(0)->getRes();
        else
            currRes = head->getTarget()->getRes();
    }
    else {
        currRes = res;
    }
    for (int i = position[0] - SEARCH_RADIUS; i <= (position[0] + SEARCH_RADIUS); i++) {
        if (i >= 0 && i < currRes->getResDim(0)) {
            for (int j = position[1] - SEARCH_RADIUS; j <= position[1] + SEARCH_RADIUS; j++) {
                if (j >= 0 && j < currRes->getResDim(1)) {
                    for (int k = position[2] - SEARCH_RADIUS; k <= position[2] + SEARCH_RADIUS; k++) {
                        if (k >= 0 && k < currRes->getResDim(2)) {
                            if (currRes->getNeuron(i, j, k)->getCue() > 0 && currRes->getNeuron(i, j, k)->isAlive()) {
                                insertSynapse(new Synapse(currRes->getNeuron(i, j, k)->getCue()/26, currRes->getNeuron(i, j, k), origin));
                            }
                        }
                    }
                }
            }
        }
    }
}

// Might not use this.
void Axon::retractSynapses() {
    // Check the list for any Synapses that need removing (below threshold).
    Synapse* curr = head;
    Synapse* prev = head;
    while (curr) {
        if (curr->getLifespan() <= 0) {
            Synapse* temp = curr->getNext();
            removeSynapse(curr);
            curr = temp;
        }
        else {
            prev = curr;
            curr = curr->getNext();
        }
    }
}

void Axon::removeSynapse(Synapse* target) {
//    if (origin->getX() == 1 && origin->getY() == 1 && origin->getZ() == 3)
//        printf ("This guy");
    // Remove the Synapse from the linked list.
    Synapse* curr = head->getNext();
    Synapse* prev = head;
    if (head == target) {
        head = head->getNext();
        if (head == NULL) {
            tail = NULL;
        }
        delete prev;
        numSynapses -= 1;
        return;
    }
    while (curr) {
        if (curr == target) {
            if (curr == tail) {
                tail = prev;
            }
            prev->setNext(curr->getNext());
            delete curr;
            numSynapses -= 1;
            return;
        }
        prev = curr;
        curr = curr->getNext();
    }
    return;
}

void Axon::insertSynapse(Synapse* target) {
//    if (origin->getX() == 1 && origin->getY() == 1 && origin->getZ() == 3)
//        printf ("This guy");
    // Insert the Synapse into the linked list.
    if (head == NULL || numSynapses == 0) {
        head = target;
        tail = target;
        numSynapses += 1;
        return;
    }
    tail->setNext(target);
    tail = target;
    numSynapses += 1;
    return;
}

void Axon::passSignal(float value) {
    // Reset axon if it no longer has any synapses.
    if (numSynapses == 0) {
        position[0] = origin->getX();
        position[1] = origin->getY();
        position[2] = origin->getZ();
        length = 0;
    }
    // Iterates through the array of synapses and calls their trigger().
//    Synapse* curr = head;
//    while (curr) {
//        curr->trigger(value);
//        curr = curr->getNext();
//    }

    // Grows the axon.
    setDirection();
    growDirection();
}

Synapse* Axon::getSynapseHead() {
    return head;
}

int Axon::getNumSynapses() {
    return numSynapses;
}

void Axon::printPosition() {
    printf ("%d %d %d\n", position[0], position[1], position[2]);
}

Axon::~Axon()
{
    if (head != NULL) {
        head->deleteAll();
    }
//    for (int i = 0; i < maxSynapses; i++) {
//        if (synapse[i] != NULL) {
//            delete synapse[i];
//        }
//    }
//    logger (file, "Axon destroyed.\n");
}
