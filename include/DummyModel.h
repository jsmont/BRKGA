#ifndef __DUMMY_MODEL__
#define __DUMMY_MODEL__

#include "Brkga.h"

class DummyModel : virtual public FitnessModel {

public:
    float getFitness(vector<float> chromosome);

};

#endif
