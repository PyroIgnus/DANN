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
        Synapse(float weight, Neuron* target, Neuron* origin);

        void trigger(float value, bool train);
        Neuron* getTarget();
        void setTarget(Neuron* target);
        Synapse* getNext();
        void setNext(Synapse* next);
        void depreciate(float value);
        void changeWeight(float value);
        void changeLifespan(float lifespan);
        void makePerm();
        float getWeight();
        float getLifespan();

        /** Default destructor */
        virtual ~Synapse();
        void deleteAll();
    protected:
    private:

        float weight;
        float lifespan;
        bool permanent;
        Neuron* target;
        Synapse* next;

        Neuron* origin;

};

#endif // SYNAPSE_H
