#include "NeuralNetwork.h"
#include <queue>
#include <list>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

// Default Constructor
NeuralNetwork::NeuralNetwork()
{
    char buff[200];
    sprintf(buff, "Creating Neural Network.\nCue initialization seed: %d\nNumber of Reservoirs: %d\nReservoir dimension size: %dx%dx%d\nNumber of max inputs: %d\nMax axon length: %d\nMax number of synapses: %d\n",
            CUE_SEED, NUM_RESERVOIRS, MAX_RES_SIZE, MAX_RES_SIZE, MAX_RES_SIZE, MAX_INPUTS, MAX_AXON_LENGTH, MAX_SYNAPSES);
    logger (file, buff);
    sprintf(buff, "Search Radius: %d\nAction Potential: %d\nThreshold: %d\nAlpha learning rate(cue): %f\nBeta learning rate(weight): %f\nSynapse lifespan increase: %f\nSynapse lifespan decrease: %f\n",
            SEARCH_RADIUS, ACTION_POTENTIAL, THRESHOLD, CUE_CHANGE, WEIGHT_CHANGE, LIFESPAN_INCREASE, LIFESPAN_DECREASE);
    logger (file, buff);
    numReservoirs = NUM_RESERVOIRS;
    resDimension = MAX_RES_SIZE;
    numSensors = NUM_SENSORS;
    numMotors = NUM_MOTORS;
    maxInputs = MAX_INPUTS;
    maxAxonLength = MAX_AXON_LENGTH;
    maxSynapses = MAX_SYNAPSES;

    criticalPeriod = false;
    sensitivityPeriod = false;

    // Create Neurons.
    for (int i = 0; i < numSensors; i++) {
        sensors[i] = new Neuron(-10 - i - i, -10 - i - i, -10 - i - i);
    }
    for (int i = 0; i < numReservoirs; i++) {
        reservoir[i] = new Reservoir(resDimension);
    }
    for (int i = 0; i < numMotors; i++) {
        motors[i] = new Neuron(resDimension + 10 + i + i, resDimension + 10 + i + i, resDimension + 10 + i + i);
        motors[i]->makeOutput(true);
    }
    // Force link sensors and motors and reservoirs.  Unique to the network.
    int sensorCount = 0;
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 7; j++) {
            for (int k = 0; k < 7; k++) {
                linkSensor(sensors[sensorCount], reservoir[i]->getNeuron(0, j, k));
                sensorCount += 1;
            }
        }
    }
    int counter = 0;
    for (int i = 0; i < 16; i++) {
        linkReservoir(reservoir[i]->getNeuron(6, 3, 3), reservoir[16]->getNeuron(0, 3 + (i > 6) + (i > 11), counter % 7));
        counter += 1;
    }
//    linkReservoir(reservoir[0]->getNeuron(1, 1, 0), reservoir[1]->getNeuron(0, 1, 1));
//    linkReservoir(reservoir[1]->getNeuron(1, 1, 0), reservoir[1]->getNeuron(1, 1, 2));
    counter = 0;
    for (int i = 0; i < numMotors; i++) {
        linkMotor(reservoir[16]->getNeuron(resDimension - 1, 3 + (i > 6), counter % 7), motors[i]);
        counter += 1;
    }

    logger (file, "Neural Network Successfully Created.\n");
}

// Might not use.
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
    target->setCue(1.0);
}

void NeuralNetwork::linkReservoir(Neuron* source, Neuron* target) {
    source->getAxon()->forceLink(target);
}

void NeuralNetwork::trainAND() {
    // Start timing.
    struct timeval start_time, end_time;
	gettimeofday(&start_time,NULL);
	double t1=start_time.tv_sec+(start_time.tv_usec/1000000.0);

    // Method to train.  Probably specific to what the DANN is being trained for.
    std::vector<float> values;
    values.resize(NUM_SENSORS);
//    printf ("Test? (y[1]/n[2]): ");
    int input = 0;
    int correct = 0;
    int iterations = 0;
    srand(0);

//    fscanf (stdin, "%d", &input);
    while (true) {
//        usleep(999999);

//        if (input == 1) {
            // Test all combinations of 0 and 1 to see if the correct output is made.
            for (int i = 0; i < 2; i++) {
                values[0] = i * 100;
                for (int j = 0; j < 2; j++) {
                    values[1] = j * 100;
                    updateSensors(values);
                    process(false);
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
            process(true);
            // Use updateCues() to update cues.
            if (motors[0]->isTriggered() != ((values[0] != 0) && (values[1] != 0))) {
                updateCues(motors[0], motors[0]->isTriggered());
            }
            else {
                //updateCues(motors[0], false);
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

    gettimeofday(&end_time,NULL);
    double t2=end_time.tv_sec+(end_time.tv_usec/1000000.0);
    double totaltime=t2-t1;

    printf ("Network successfully learned AND gate behaviour in %d iterations.\n", iterations);
    if (LOGGING) {
        char buff[100];
        sprintf(buff, "Network successfully learned AND gate behaviour in %d iterations and %.6lf seconds.\n", iterations, totaltime);
        logger(file, buff);
    }
}

void NeuralNetwork::trainOR() {
    // Start timing.
    struct timeval start_time, end_time;
	gettimeofday(&start_time,NULL);
	double t1=start_time.tv_sec+(start_time.tv_usec/1000000.0);

    // Method to train.  Probably specific to what the DANN is being trained for.
    std::vector<float> values;
    values.resize(NUM_SENSORS);
//    printf ("Test? (y[1]/n[2]): ");
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
                    process(false);
                    if (motors[0]->isTriggered() == (i || j)) {
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
            process(true);
            // Use updateCues() to update cues.
            if (motors[0]->isTriggered() != (values[0] || values[1])) {
                updateCues(motors[0], motors[0]->isTriggered());
            }
            else {
                //updateCues(motors[0], false);
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

    gettimeofday(&end_time,NULL);
    double t2=end_time.tv_sec+(end_time.tv_usec/1000000.0);
    double totaltime=t2-t1;

    printf ("Network successfully learned OR gate behaviour in %d iterations.\n", iterations);
    if (LOGGING) {
        char buff[100];
        sprintf(buff, "Network successfully learned OR gate behaviour in %d iterations and %.6lf seconds.\n", iterations, totaltime);
        logger(file, buff);
    }
}

void NeuralNetwork::trainXOR() {
    // Start timing.
    struct timeval start_time, end_time;
	gettimeofday(&start_time,NULL);
	double t1=start_time.tv_sec+(start_time.tv_usec/1000000.0);

    // Method to train.  Probably specific to what the DANN is being trained for.
    std::vector<float> values;
    values.resize(NUM_SENSORS);
//    printf ("Test? (y[1]/n[2]): ");
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
                    process(false);
                    if (motors[0]->isTriggered() == (i ^ j)) {
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
            process(true);
            // Use updateCues() to update cues.
            int i = 0;
            int j = 0;
            if (values[0] > 0)
                i = 1;
            if (values[1] > 0)
                j = 1;
            if (motors[0]->isTriggered() != (i ^ j)) {
                updateCues(motors[0], motors[0]->isTriggered());
            }
            else {
                //updateCues(motors[0], false);
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

    gettimeofday(&end_time,NULL);
    double t2=end_time.tv_sec+(end_time.tv_usec/1000000.0);
    double totaltime=t2-t1;

    printf ("Network successfully learned XOR gate behaviour in %d iterations.\n", iterations);
    if (LOGGING) {
        char buff[100];
        sprintf(buff, "Network successfully learned XOR gate behaviour in %d iterations and %.6lf seconds.\n", iterations, totaltime);
        logger(file, buff);
    }
}

void NeuralNetwork::trainMNIST(int numTrain, int numTest) {
    // Start timing.
    struct timeval start_time, end_time;
	gettimeofday(&start_time,NULL);
	double t1=start_time.tv_sec+(start_time.tv_usec/1000000.0);

    int*** trainValues = new int** [numTrain];
    for (int i = 0; i < numTrain; i++) {
        trainValues[i] = new int* [28];
        for (int j = 0; j < 28; j++) {
            trainValues[i][j] = new int [28];
        }
    }
    int* trainLabels = new int [numTrain];
    int*** testValues = new int** [numTest];
    for (int i = 0; i < numTest; i++) {
        testValues[i] = new int* [28];
        for (int j = 0; j < 28; j++) {
            testValues[i][j] = new int [28];
        }
    }
    int* testLabels = new int [numTest];
    if (readMNIST(MNIST_TRAIN_IMAGES, MNIST_TRAIN_LABELS, numTrain, trainValues, trainLabels) == -1)
        return;
    if (readMNIST(MNIST_TEST_IMAGES, MNIST_TEST_LABELS, numTest, testValues, testLabels) == -1)
        return;

    // Method to train MNIST data.
    for (int i = 0; i < numTrain; i++) {
        if (i % (numTrain/8) == 0 && (i != 0)) {
            printf ("Completed another 12.5%% of training.\n");
        }
        updateSensorsMNIST(trainValues[i]);
        process(true);
        for (int j = 0; j < numMotors; j++) {
//            if (motors[j]->isTriggered()) {
//                printf ("Motor %d turned on.\n", j);
//            }
            if (motors[j]->isTriggered() && (j != trainLabels[i]) || (!motors[j]->isTriggered() && (j == trainLabels[i]))) {
                updateCues(motors[j], motors[j]->isTriggered());
            }
            motors[j]->resetTrigger();
        }
    }
    printf ("Training Complete.\n");

    // Method to test MNIST data.
    bool right = false;
    int wrong = 0;
    int correct = 0;
    int partially[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < numTest; i++) {
        if (i % (numTest/8) == 0 && (i != 0)) {
            printf ("Completed another 12.5%% of testing.\n");
        }
        updateSensorsMNIST(testValues[i]);
        process(false);
        if (motors[testLabels[i]]->isTriggered()) {
            right = true;
        }
        if (i % 100 == 0) {
            printf("0 1 2 3 4 5 6 7 8 9\n");
        }
        for (int j = 0; j < numMotors; j++) {
            if (i % 100 == 0) {
                if (motors[j]->isTriggered())
                    printf ("* ");
                else {
                    printf("  ");
                }
            }
            if (!motors[j]->isTriggered() && (j == testLabels[i])) {
                motors[j]->resetTrigger();
                j = numMotors;
            }
            else {
                if (motors[j]->isTriggered() && (j != testLabels[i])) {
                    wrong += 1;
                }
                motors[j]->resetTrigger();
            }
        }
        if (right) {
            if (wrong > 0) {
                partially[wrong - 1] += 1;
            }
            else {
                correct += 1;
            }
            right = false;
        }
        printf ("\n");
        wrong = 0;
    }

    gettimeofday(&end_time,NULL);
    double t2=end_time.tv_sec+(end_time.tv_usec/1000000.0);
    double totaltime=t2-t1;

    printf ("Network successfully completed MNIST training and testing in %.6lf seconds.\n", totaltime);
    printf ("Correct: %d\n", correct);
    for (int i = 0; i < 9; i++) {
        printf ("Partially correct (%d wrong): %d\n", i + 1, partially[i]);
    }
    if (LOGGING) {
        char buff[100];
        sprintf(buff, "Network successfully completed MNIST training and testing in %.6lf seconds with %d correct and %d partially correct.\n", totaltime, correct, partially);
        logger(file, buff);
    }

    for (int i = 0; i < numTrain; i++) {
        for (int j = 0; j < 28; j++) {
            delete[] trainValues[i][j];
        }
        delete[] trainValues[i];
    }
    delete[] trainValues;
    delete[] trainLabels;
    for (int i = 0; i < numTest; i++) {
        for (int j = 0; j < 28; j++) {
            delete[] testValues[i][j];
        }
        delete[] testValues[i];
    }
    delete[] testLabels;
}

void NeuralNetwork::updateSensors(std::vector<float> values) {
    // Update sensor Neuron dendrite values.  Specific to each Sensor.
    for (int i = 0; i < values.size(); i++) {
        sensors[i]->acceptSignal(values[i], NULL);
    }
}

void NeuralNetwork::updateSensorsMNIST(int** values) {
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 28; j++) {
            sensors[(28 * i) + j]->acceptSignal(values[i][j], NULL);
        }
    }
}

void NeuralNetwork::process(bool train) {
    // Commence a breadth first signal pass starting from the sensor Neurons.
    std::list<Neuron*> unprocessed;
    std::list<Neuron*> processed;
    Neuron* current;
    Neuron* check;
    Synapse* head;
    Synapse* curr;
    bool isUnique = true;

    for (int i = 0; i < numSensors; i++) {
        unprocessed.push_back(sensors[i]);
    }

//    int counter = 0;

    while (!unprocessed.empty()) {

        // Process the next Neuron.
        current = unprocessed.front();
//        counter += 1;
//        printf ("%d ", current->getAxon()->getNumSynapses());
//        current->printPosition();
        curr = current->getAxon()->getSynapseHead();
        int numSynapses = current->getAxon()->getNumSynapses();
        // Send an action potential if necessary.
        if (current->activatePotential(current->process())) {
            // Add new Neurons to the queue if necessary
            for (int i = 0; i < numSynapses; i++) {
                isUnique = true;
                check = curr->getTarget();
                curr->trigger(ACTION_POTENTIAL * curr->getWeight(), train);
                // Check for duplicates before pushing new Neurons into the queue.
                for (std::list<Neuron*>::iterator it = processed.begin(); it != processed.end(); ++it) {
                    if ((*it)->equals(check)) {
                        isUnique = false;
                        break;
                    }
                }
                if (isUnique) {
                    for (std::list<Neuron*>::iterator it = unprocessed.begin(); it != unprocessed.end(); ++it) {
                        if ((*it)->equals(check)) {
                            isUnique = false;
                            break;
                        }
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

//    printf ("%d neurons processed.\n", counter);

// Used to empty all dendrites.  Most likely won't use.
//    for (int res = 0; res < numReservoirs; res++) {
//        for (int i = 0; i < resDimension; i++) {
//            for (int j = 0; j < resDimension; j++) {
//                for (int k = 0; k < resDimension; k++) {
//                    current = reservoir[res]->getNeuron(i, j, k);
//                    current->resetDendrites();
//                }
//            }
//        }
//    }
}

void NeuralNetwork::updateCues(Neuron* motor, bool reinforce) {
    // Back propagate starting from the target motor Neuron and change cues accordingly.
    // Commence a backward breadth first search starting from the motor Neuron.
    std::list<Neuron*> unprocessed;
    std::list<Neuron*> processed;
    Neuron* current;
    Neuron* check;
    bool isUnique;
    bool state = motor->isTriggered();
    int counter = 0;
    float change = CUE_CHANGE;
    if (reinforce) {
        change = change * (-1);
    }

    unprocessed.push_back(motor);
    for (int i = 0; i < numSensors; i++) {
        processed.push_back(sensors[i]);
    }

    while (!unprocessed.empty()) {

        // Process the next Neuron.
        current = unprocessed.front();
//        current->printPosition();
//        printf ("%f\n", current->getCue());
        // Add new Neurons to the queue if necessary
        for (int i = 0; i < current->getConnSize(); i++) {
            isUnique = true;
            check = current->getConnection(i);
            // Check for duplicates before pushing new Neurons into the queue.
            for (std::list<Neuron*>::iterator it = processed.begin(); it != processed.end(); it++) {
                if ((*it)->equals(check)) {
                    isUnique = false;
                    break;
                }
            }
            if (isUnique) {
                for (std::list<Neuron*>::iterator it = unprocessed.begin(); it != unprocessed.end(); it++) {
                    if ((*it)->equals(check)) {
                        isUnique = false;
                        break;
                    }
                }
            }
            if (isUnique && (check->isTriggered() == state)) {
                unprocessed.push_back(check);
            }
        }
        // Update cues if necessary.
        if (!current->isOutput()) {
            current->changeCue(change);
        }
        counter += 1;
        processed.push_front(current);
        // Remove Neuron as it has just been processed.
        unprocessed.pop_front();

    }

    Synapse* curr;
    // Update weights based on the targets' cue values and reset triggers.
    for (int res = 0; res < numReservoirs; res++) {
        for (int i = 0; i < resDimension; i++) {
            for (int j = 0; j < resDimension; j++) {
                for (int k = 0; k < resDimension; k++) {
                    current = reservoir[res]->getNeuron(i, j, k);
                    current->resetTrigger();
                    curr = current->getAxon()->getSynapseHead();
                    int numSyn = current->getAxon()->getNumSynapses();
                    for (int s = 0; s < numSyn; s++) {
                        curr->changeWeight(WEIGHT_CHANGE * curr->getTarget()->getCue());   // Some function of the target cue.
                        if (!(curr->getTarget()->isOutput())) {
                            curr->changeLifespan(-1 * LIFESPAN_DECREASE);
                        }
                        if (curr->getLifespan() <= 0) {
                            Synapse* temp = curr->getNext();
                            current->getAxon()->removeSynapse(curr);
                            curr = temp;
                            s += 1;
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
        motors[i]->resetDendrites();
    }
}

void NeuralNetwork::resetMotorTriggers() {
    for (int i = 0; i < numMotors; i++) {
        motors[i]->resetTrigger();
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

