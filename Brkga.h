#ifndef __BRKGA__
#define __BRKGA__

#include<vector>
using namespace std;

typedef int (*FitnessFunction)(vector<float>); 

typedef struct Individual{
    vector<float> chromosome;
    int fitness;
    //Individual();
    Individual(int chromosomeLength);
    void print();
} Individual;

class Brkga {

    int numIterations;
    int populationSize;
    int chromosomeLength;
    int numElite;
    int numNormies;
    float ro;

    FitnessFunction fitness;
    
    vector<Individual> population;
    
public:

    Brkga(int chromosomeLength, int populationSize, int numElite, int numNormies, float ro, FitnessFunction fitness);

    vector<int> run(int numIterations);

    vector<int> getBest();

private:

    vector<Individual> createMutants(int number);

    vector<Individual> rankIndividuals(vector<Individual> population);
    vector<Individual> assignFitness(vector<Individual> population);

    vector<Individual> createNewGeneration(vector<Individual> population);
    vector<Individual> getElite(vector<Individual> population);
    vector<Individual> getNormies(vector<Individual> population);

    vector<Individual> crossoverNormies(vector<Individual> elite, vector<Individual> normies, int numRemixed);

    Individual crossoverNormie(Individual elite, Individual normie);
    
};

#endif
