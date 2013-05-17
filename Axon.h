#ifndef AXON_H
#define AXON_H

#include "Synapse.h"
#include "utils.h"
#include "global.h"

class Synapse;

class Axon
{
    public:
        /** Default constructor */
        Axon();
        Axon(int x, int y, int z);
        Axon(int x, int y, int z, float cue);

        void setDirection();
        void growDirection();
        void createSynapses();
        void removeSynpase();
        void passSignal(float value);

        /** Default destructor */
        virtual ~Axon();
    protected:
    private:

        int maxAxonLength;
        int maxSynapses;

        float cue;
        int position[MAX_AXON_LENGTH][3];
        float direction[3];
        Synapse* synapse[MAX_SYNAPSES];
};

#endif // AXON_H
