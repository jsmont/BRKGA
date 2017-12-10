#include "DummyModel.h"
#include <iostream>

float DummyModel::getFitness(vector<float> chromosome){

    float sum = 0;
    
    for(int i = 0; i < chromosome.size(); ++i){
        sum += (i+1)*chromosome[i];
    }

    return sum;
}

int DummyModel::getChromosomeLength(){
    return 5;
}
