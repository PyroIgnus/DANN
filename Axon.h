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
        Axon(int x, int y, int z);
        Axon(int x, int y, int z, float cue);

        void setDirection();
        void growDirection();
        void createSynapses();  // This should create the new Synapse objects in the array and connect them only to Neurons in the positive xyz region (within the Reservoir).
        void createSynapse(Neuron* target);
        void removeSynpase();   // This should remove the Synapse object from the array.
        void passSignal(float value);
        Synapse* getSynapse (int index);
        int getNumSynapses();


        /** Default destructor */
        virtual ~Axon();
    protected:
    private:

        int maxAxonLength;
        int maxSynapses;

        float cue;
        int position[MAX_AXON_LENGTH][3];
        float direction[3];
        Synapse* synapse[MAX_SYNAPSES]; // There can not be any empty synapse elements between non-empty elements.  If this is unavoidable or really slow, find another way to do this and tell me.
        int numSynapses;
};

#endif // AXON_H
