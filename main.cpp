#include<iostream>
using namespace std;

#include "Brkga.h"

float fitness(vector<float> chromosome){
    float sum = 0;
    
    for(int i = 0; i < chromosome.size(); ++i){
        sum += i*chromosome[i];
    }

    return sum;
}

int main(){
    
    int chromosomeLength = 4;
    int populationSize = 3;
    int numElite = 1;
    int numNormies = 1;
    float ro = 0.7;

    Brkga instance = Brkga(chromosomeLength, populationSize, numElite, numNormies, ro, fitness);

    instance.run(1);
}
