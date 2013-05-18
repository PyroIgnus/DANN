#ifndef SYNAPSE_H
#define SYNAPSE_H

#include "Neuron.h"
#include "global.h"
#include "utils.h"

class Neuron;

class Synapse
{
    public:
        /** Default constructor */
        Synapse();
        Synapse(Neuron* target);

        void trigger(float value);
        Neuron* getTarget();
        void setTarget(Neuron* target);
        Synapse* getNext();
        void setNext(Synapse* next);
        void depreciate(float value);

        /** Default destructor */
        virtual ~Synapse();
    protected:
    private:

        float weight;
        Neuron* target;
        Synapse* next;

};

#endif // SYNAPSE_H
