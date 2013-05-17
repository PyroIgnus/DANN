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
         * @arg filename Accepts a string for the filen name of the network matrix.
         */
        NeuralNetwork(char* filename);

        void train();
        void updateSensors();
        void process();
        void determineState();

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
