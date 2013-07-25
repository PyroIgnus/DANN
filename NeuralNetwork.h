#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "Reservoir.h"
#include "Neuron.h"
#include "utils.h"
#include "global.h"

class NeuralNetwork
{
    public:
        /**
         * @brief Default Constructor
         */
        NeuralNetwork();

        /**
         * @brief Constructor that initializes its neurons based on the file read.
         * @arg filename Accepts a string for the file name of the network matrix.
         */
        NeuralNetwork(char* filename);  // Might not use.

        void linkSensor(Neuron* sensor, Neuron* target);
        void linkMotor(Neuron* target, Neuron* motor);
        void linkReservoir(Neuron* source, Neuron* target);
        void trainAND();
        void trainOR();
        void trainXOR();
        void trainMNIST(int numTrain, int numTest);
        void updateSensors(std::vector<float> values);
        void updateSensorsMNIST(int** values);
        void process(bool train);
        void updateCues(Neuron* motor, bool reinforce); // If reinforce is true, cues will be decreased.
        void determineState();  // This is to make the net learn "autonomously".
        void outputMotors();

        /** Default destructor */
        virtual ~NeuralNetwork();
    protected:
    private:

        int numReservoirs;
        int resDimension;
        int numSensors;
        int numMotors;
        int maxInputs;
        int maxAxonLength;
        int maxSynapses;

        bool criticalPeriod;
        bool sensitivityPeriod;
        Neuron* sensors[NUM_SENSORS];
        Reservoir* reservoir[NUM_RESERVOIRS];
        Neuron* motors[NUM_MOTORS];
};

#endif // NEURALNETWORK_H
