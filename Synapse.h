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
        Synapse(Neuron* target, Neuron* origin);

        void trigger(float value);
        Neuron* getTarget();
        void setTarget(Neuron* target);
        Synapse* getNext();
        void setNext(Synapse* next);
        void depreciate(float value);
        void changeWeight(float value);
        float getWeight();

        /** Default destructor */
        virtual ~Synapse();
        void deleteAll();
    protected:
    private:

        float weight;
        Neuron* target;
        Synapse* next;

        Neuron* origin;

};

#endif // SYNAPSE_H
