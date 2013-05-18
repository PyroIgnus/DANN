#ifndef NEURON_H
#define NEURON_H

#include "Axon.h"
#include "utils.h"
#include "global.h"

class Axon;

class Neuron
{
    public:
        /** Default constructor */
        Neuron();
        Neuron(int x, int y, int z);
        Neuron(int x, int y, int z, float cue);

        void acceptSignal(float value);
        float process();
        void activatePotential(float value);
        bool equals (Neuron* other);
        int getX();
        int getY();
        int getZ();
        Axon* getAxon();

        /** Default destructor */
        virtual ~Neuron();
    protected:
    private:

        int maxInputs;
        int maxAxonLength;
        int maxSynapses;

        /**
         * @brief Describes the attractive/repulsive cue this neuron possesses.  A value of 0 indicates an negative, 1 a positive and -1 a terminal.
         */
        float cue;
        bool alive;
        int position[3];
        float dendrites[MAX_INPUTS];
        int numDendritesActive;
        int threshold;
        int recoveryPeriod;
        int recoveryThreshold;
        Axon* axon;
};

#endif // NEURON_H
