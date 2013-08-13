#ifndef RESERVOIR_H
#define RESERVOIR_H

#include "Neuron.h"
#include "utils.h"
#include "global.h"
#include <vector>

class Neuron;

class Reservoir
{
    public:
        /** Default constructor */
        Reservoir();

        /** Default constructor */
        Reservoir(int resDimension);
        Reservoir(int x, int y, int z);

        Neuron* getNeuron (int x, int y, int z);
        int getResDim (int dim);

        /** Default destructor */
        virtual ~Reservoir();
    protected:
    private:

        int resSize[3];
        int maxInputs;
        int maxAxonLength;
        int maxSynapses;

//        Neuron* neurons[MAX_RES_SIZE][MAX_RES_SIZE][MAX_RES_SIZE];
        std::vector<std::vector<std::vector<Neuron*> > > neurons;

        float neuronSynapseDensity;
};

#endif // RESERVOIR_H
