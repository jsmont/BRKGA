#ifndef __BRKGA__
#define __BRKGA__

#include<vector>
#include <iostream>
using namespace std;

typedef struct Individual{
    vector<float> chromosome;
    float fitness;
    Individual();
    Individual(int chromosomeLength);
    void print();
    bool operator<(const Individual& other) const;

} Individual;

class FitnessModel {

public:
    virtual float getFitness(vector<float> chromosome) = 0;
    virtual int getChromosomeLength() = 0;

};

class Brkga {

    int numIterations;
    int populationSize;
    int chromosomeLength;
    int numElite;
    int numNormies;
    float ro;

    FitnessModel* model;
    
    vector<Individual> population;
    
public:

    Brkga(int populationSize, int numElite, int numNormies, float ro, FitnessModel* model);

    float run(int numIterations);

    vector<float> getBest();

    static void printChromosome(vector<float> chromosome);

private:

    vector<Individual> createMutants(int number);

    vector<Individual> rankIndividuals(vector<Individual> population);
    vector<Individual> assignFitness(vector<Individual> population);

    vector<Individual> createNewGeneration(vector<Individual> population);
    vector<Individual> getElite(vector<Individual> population);
    vector<Individual> getNormies(vector<Individual> population);

    vector<Individual> crossoverNormies(vector<Individual> elite, vector<Individual> normies, int numRemixed);

    Individual crossoverNormie(Individual elite, Individual normie);

    float getBestFitness(vector<Individual> population);

    void inspectPopulation(vector<Individual> population);
    
};

#endif
