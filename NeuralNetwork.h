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
        NeuralNetwork(char* filename);

        void linkSensor(Neuron* sensor, Neuron* target);
        void linkMotor(Neuron* target, Neuron* motor);
        void trainAND();
        void trainOR();
        void updateSensors(std::vector<float> values);
        void process();
        void updateCues(Neuron* motor, bool reinforce);
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
