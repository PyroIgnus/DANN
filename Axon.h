#ifndef AXON_H
#define AXON_H

#include "Synapse.h"
#include "utils.h"
#include "global.h"
#include <vector>

class Synapse;
class Neuron;

class Axon
{
    public:
        /** Default constructor */
        Axon();
        Axon(int x, int y, int z, Neuron* origin);

        void setDirection();
        void growDirection();
        void forceLink(Neuron* target);
        void createSynapses();  // This should create the new Synapse objects in the array and connect them only to Neurons in the positive xyz region (within the Reservoir).
        void retractSynapses();   // This will iterate through the linked list and remove Synapses below threshold.
        void removeSynapse(Synapse* target);
        void insertSynapse(Synapse* target);
        void passSignal(float value);
        Synapse* getSynapseHead ();
        int getNumSynapses();


        /** Default destructor */
        virtual ~Axon();
    protected:
    private:

        int maxAxonLength;
        int maxSynapses;

        int position[MAX_AXON_LENGTH][3];
        float direction[3];
        Synapse* head;
        Synapse* tail;
        //Synapse* synapse[MAX_SYNAPSES]; // There can not be any empty synapse elements between non-empty elements.  If this is unavoidable or really slow, find another way to do this and tell me.
        int numSynapses;

        Neuron* origin;
};

#endif // AXON_H
