#ifndef __BRKGA__
#define __BRKGA__

#include<vector>
using namespace std;

typedef float (*FitnessFunction)(vector<float>); 

typedef struct Individual{
    vector<float> chromosome;
    float fitness;
    //Individual();
    Individual(int chromosomeLength);
    void print();
    bool operator>(const Individual& other) const;
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

    float run(int numIterations);

    vector<float> getBest();

private:

    vector<Individual> createMutants(int number);

    vector<Individual> rankIndividuals(vector<Individual> population);
    vector<Individual> assignFitness(vector<Individual> population);

    vector<Individual> createNewGeneration(vector<Individual> population);
/*    vector<Individual> getElite(vector<Individual> population);
    vector<Individual> getNormies(vector<Individual> population);

    vector<Individual> crossoverNormies(vector<Individual> elite, vector<Individual> normies, int numRemixed);

    Individual crossoverNormie(Individual elite, Individual normie);
*/
    float getBestFitness(vector<Individual> population);

    void inspectPopulation(vector<Individual> population);
    
};

#endif
