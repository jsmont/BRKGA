#include<iostream>
using namespace std;

#include "Brkga.h"

int fitness(vector<float> f){
    return 1;
}

int main(){
    
    int chromosomeLength = 4;
    int populationSize = 3;
    int numElite = 1;
    int numNormies = 1;
    float ro = 0.7;

    Brkga instance = Brkga(chromosomeLength, populationSize, numElite, numNormies, ro, fitness);

}
