#ifndef SYNAPSE_H
#define SYNAPSE_H

#include "Neuron.h"
#include "global.h"

class Neuron;

class Synapse
{
    public:
        /** Default constructor */
        Synapse();
        Synapse(Neuron* target);

        void trigger(float value);

        /** Default destructor */
        virtual ~Synapse();
    protected:
    private:

        float weight;
        Neuron* target;

};

#endif // SYNAPSE_H
