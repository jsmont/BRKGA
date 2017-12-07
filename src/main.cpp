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
    int populationSize = 500;
    int numElite = 10;
    int numNormies = 390;
    float ro = 0.7;

    int remainingIterations = 10000;
    int batch = remainingIterations/100;

    Brkga instance = Brkga(chromosomeLength, populationSize, numElite, numNormies, ro, fitness);

    while (remainingIterations > batch){
        float fitness = instance.run(batch);
        cout << "Remaining iterations: " << remainingIterations << "\tFitness: " << fitness << endl;
        remainingIterations-=batch;
    }

    float fitness = instance.run(remainingIterations);
    cout << "Remaining iterations: 0\tFitness: " << fitness << endl;
}
