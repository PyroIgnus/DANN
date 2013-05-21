#ifndef NEURON_H
#define NEURON_H

#include "Axon.h"
#include "utils.h"
#include "global.h"
#include <vector>

class Axon;

class Neuron
{
    public:
        /** Default constructor */
        Neuron();
        Neuron(int x, int y, int z);
        Neuron(int x, int y, int z, float cue);

        void addConnection(Neuron* source);
        void removeConnection(Neuron* source);
        void acceptSignal(float value, Neuron* source);
        float process();
        void activatePotential(float value);
        void changeCue(float value);
        bool equals (Neuron* other);
        int getX();
        int getY();
        int getZ();
        Axon* getAxon();
        Neuron* getConnection(int index);
        int getConnSize();

        /** Default destructor */
        virtual ~Neuron();
    protected:
    private:

        int maxInputs;
        int maxAxonLength;
        int maxSynapses;

        /**
         * @brief Describes the attractive/repulsive cue this neuron possesses.
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

        std::vector<Neuron*> connection;
        int numConnections;
        std::vector<int> counter;
};

#endif // NEURON_H
