#include "NeuralNetwork.h"
#include <queue>
#include <list>
#include <stdlib.h>
#include <unistd.h>

// Default Constructor
NeuralNetwork::NeuralNetwork()
{
    logger (file, "Creating Neural Network.\n");
    numReservoirs = NUM_RESERVOIRS;
    resDimension = MAX_RES_SIZE;
    numSensors = NUM_SENSORS;
    numMotors = NUM_MOTORS;
    maxInputs = MAX_INPUTS;
    maxAxonLength = MAX_AXON_LENGTH;
    maxSynapses = MAX_SYNAPSES;

    criticalPeriod = false;
    sensitivityPeriod = false;

    for (int i = 0; i < numSensors; i++) {
        sensors[i] = new Neuron(-10, -10, -10);
    }
    for (int i = 0; i < numReservoirs; i++) {
        reservoir[i] = new Reservoir(resDimension);
    }
    for (int i = 0; i < numMotors; i++) {
        motors[i] = new Neuron(resDimension + 10, resDimension + 10, resDimension + 10);
    }
    for (int i = 0; i < numSensors; i++) {
        linkSensor(sensors[i], reservoir[0]->getNeuron(i, 0, 0));
    }
    for (int i = 0; i < numMotors; i++) {
        linkMotor(reservoir[0]->getNeuron(resDimension - 1, resDimension - 1, i), motors[i]);
    }

    logger (file, "Neural Network Successfully Created.\n");
}

NeuralNetwork::NeuralNetwork(char* filename)
{


}

void NeuralNetwork::linkSensor(Neuron* sensor, Neuron* target) {
    // Link the sensor Neuron to target Neuron by means of axon and synapses.
    sensor->getAxon()->forceLink(target);
}

void NeuralNetwork::linkMotor(Neuron* target, Neuron* motor) {
    // Link the target Neuron to motor Neuron by means of axon and synapses.
    target->getAxon()->forceLink(motor);
}

void NeuralNetwork::trainAND() {
    // Method to train.  Probably specific to what the DANN is being trained for.
    std::vector<float> values;
    values.resize(NUM_SENSORS);
    printf ("Test? (y[1]/n[2]): ");
    int input = 0;
    int correct = 0;
    int iterations = 0;
    srand(0);

//    fscanf (stdin, "%d", &input);
    while (true) {
        //usleep(999999);

//        if (input == 1) {
            // Test all combinations of 0 and 1 to see if the correct output is made.
            for (int i = 0; i < 2; i++) {
                values[0] = i * 100;
                for (int j = 0; j < 2; j++) {
                    values[1] = j * 100;
                    updateSensors(values);
                    process();
                    if (motors[0]->isTriggered() == (i && j)) {
                        correct += 1;
                        motors[0]->resetTrigger();
                    }
                }
            }
            printf ("The DANN obtained a score of %d out of 4.\n", correct);
            if (correct == 4) {
                break;
            }
            correct = 0;
//        }
//        else if (input == 2) {
            // Run through a random combination to train.
            values[0] = (rand() % 2) * 100;
            values[1] = (rand() % 2) * 100;
            updateSensors(values);
            process();
            // Use updateCues() to update cues.
            if (values[0] && values[1]) {
                updateCues(motors[0], true);
            }
            else {
                updateCues(motors[0], false);
            }
            // Show input-output relation.
            if (values[0]) {
                printf ("Input 0 is on.\n");
            }
            else {
                printf ("Input 0 is off.\n");
            }
            if (values[1]) {
                printf("Input 1 is on.\n");
            }
            else {
                printf ("Input 1 is off.\n");
            }
            outputMotors();
            iterations += 1;
//        }
//        printf ("Test? (y/n): ");
//        fscanf(stdin, "%d", &input);
    }
    printf ("Network successfully learned AND gate behaviour in %d iterations.\n", iterations);
}

void NeuralNetwork::updateSensors(std::vector<float> values) {
    // Update sensor Neuron dendrite values.  Specific to each Sensor.
    for (int i = 0; i < values.size(); i++) {
        sensors[i]->acceptSignal(values[i], NULL);
    }
}

void NeuralNetwork::process() {
    // Commence a breadth first signal pass starting from the sensor Neurons.
    std::list<Neuron*> unprocessed;
    std::list<Neuron*> processed;
    Neuron* current;
    Neuron* check;
    Synapse* head;
    Synapse* curr;
    bool isUnique;

    for (int i = 0; i < numSensors; i++) {
        unprocessed.push_back(sensors[i]);
    }

    while (!unprocessed.empty()) {

        // Process the next Neuron.
        current = unprocessed.front();
        head = current->getAxon()->getSynapseHead();
        curr = head;
        // Send an action potential if necessary.
        if (current->activatePotential(current->process())) {
            // Add new Neurons to the queue if necessary
            isUnique = true;
            for (int i = 0; i < current->getAxon()->getNumSynapses(); i++) {
                check = curr->getTarget();
                // Check for duplicates before pushing new Neurons into the queue.
                for (std::list<Neuron*>::iterator it = processed.begin(); it != processed.end(); it++) {
                    if ((*it)->equals(check)) {
                        isUnique = false;
                        break;
                    }
                }
                for (std::list<Neuron*>::iterator it = unprocessed.begin(); it != unprocessed.end(); it++) {
                    if ((*it)->equals(check)) {
                        isUnique = false;
                        break;
                    }
                }
                if (isUnique) {
                    unprocessed.push_back(check);
                }
                curr = curr->getNext();
            }
        }
        processed.push_front(current);
        // Remove Neuron as it has just been processed.
        unprocessed.pop_front();

    }

    // Update the lifespan of all Synapses based on their target cues.
    for (int res = 0; res < numReservoirs; res++) {
        for (int i = 0; i < resDimension; i++) {
            for (int j = 0; j < resDimension; j++) {
                for (int k = 0; k < resDimension; k++) {
                    current = reservoir[res]->getNeuron(i, j, k);
                    current->resetTrigger();
                    head = current->getAxon()->getSynapseHead();
                    curr = head;
                    for (int i = 0; i < current->getAxon()->getNumSynapses(); i++) {
                        curr->changeWeight(WEIGHT_CHANGE * curr->getTarget()->getCue());   // Some function of the target cue.
                        if (curr->getWeight() <= 0) {
                            Synapse* temp = curr->getNext();
                            current->getAxon()->removeSynapse(curr);
                            curr = temp;
                        }
                        else {
                            curr = curr->getNext();
                        }
                    }
                }
            }
        }
    }
}

void NeuralNetwork::updateCues(Neuron* motor, bool reinforce) {
    // Back propagate starting from the target motor Neuron and change cues accordingly.
    // Commence a backward breadth first search starting from the motor Neuron.
    std::list<Neuron*> unprocessed;
    std::list<Neuron*> processed;
    Neuron* current;
    Neuron* check;
    bool isUnique;
    int counter = 0;
    float change = CUE_CHANGE;
    if (!reinforce) {
        change = change * (-1);
    }

    for (int i = 0; i < numMotors; i++) {
        unprocessed.push_back(motor);
    }
    for (int i = 0; i < numMotors; i++) {
        processed.push_back(sensors[i]);
    }

    while (!unprocessed.empty()) {

        // Process the next Neuron.
        current = unprocessed.front();
        // Add new Neurons to the queue if necessary
        isUnique = true;
        current->printPosition();
        printf ("%d\n", unprocessed.size());
        for (int i = 0; i < current->getConnSize(); i++) {
            check = current->getConnection(i);
            // Check for duplicates before pushing new Neurons into the queue.
            for (std::list<Neuron*>::iterator it = processed.begin(); it != processed.end(); it++) {
                if ((*it)->equals(check)) {
                    isUnique = false;
                    break;
                }
            }
            for (std::list<Neuron*>::iterator it = unprocessed.begin(); it != unprocessed.end(); it++) {
                if ((*it)->equals(check)) {
                    isUnique = false;
                    break;
                }
            }
            if (isUnique) {
                unprocessed.push_back(check);
            }
        }
        // Update cues if necessary.
        if (counter >= numMotors) {
            current->changeCue(change);
        }
        counter += 1;
        processed.push_front(current);
        // Remove Neuron as it has just been processed.
        unprocessed.pop_front();

    }
}

void NeuralNetwork::determineState() {
    // Check output and apply consequences (change critical/sensitivityPeriods).
}

void NeuralNetwork::outputMotors() {
    // Highly specific to what each motor Neuron is able to do.
    for (int i = 0; i < numMotors; i++) {
        if (motors[i]->isTriggered()) {
            printf ("Motor %d is on.\n", i);
            motors[i]->resetTrigger();
        }
        else {
            printf ("Motor %d is off.\n", i);
        }
    }
}

NeuralNetwork::~NeuralNetwork()
{
    logger (file, "Destroying Neural Network.\n");
    for (int i = 0; i < numSensors; i++) {
        delete sensors[i]->getAxon();
    }
    for (int i = 0; i < numMotors; i++) {
        delete motors[i]->getAxon();
    }
    for (int i = 0; i < numReservoirs; i++) {
        delete reservoir[i];
    }
    for (int i = 0; i < numSensors; i++) {
        delete sensors[i];
    }
    for (int i = 0; i < numMotors; i++) {
        delete motors[i];
    }
    logger (file, "Neural Network Successfully destroyed.\n");
}

