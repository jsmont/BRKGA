#include "Brkga.h"
#include <cstdlib>
#include<iostream>

Individual::Individual(int chromosomeLength){
    chromosome = vector<float>(chromosomeLength);

    //std::random_device rand;

    for(int i = 0; i < chromosome.size(); ++i){
        chromosome[i] = ((float)rand())/RAND_MAX;//((float)rand())/rand.max();
    }

    fitness = -1;
}

void Individual::print(){
    
   cout << "Chromosome:\t";
   if(chromosome.size() > 0){
       cout << "[ " << chromosome[0] << " ";
       for(int i = 1; i < chromosome.size(); ++i){
           cout << ",\t" << chromosome[i] << " ";
       }
       cout << " ]" << endl;

   }

   cout << "Fitness:\t" << fitness << endl;
}

Brkga::Brkga(int chromosomeLength, int populationSize, int numElite, int numNormies, float ro, FitnessFunction fitness){
    
    this->chromosomeLength = chromosomeLength;
    this->numElite = numElite;
    this->numNormies = numNormies;
    this->ro = ro;
    this->fitness = fitness;

    this->population = createMutants(populationSize);

}


vector<Individual> Brkga::createMutants(int number){

    vector<Individual> mutants = vector<Individual>(number, chromosomeLength);

    for(int i = 0; i < mutants.size(); ++i){
        mutants[i] = Individual(chromosomeLength);
    }


#ifdef VCREATEMUTANTS

    cout << endl << "[VERBOSE MUTANT CREATION]" << endl;

    for(int i = 0; i < mutants.size(); ++i){
        cout << "[MUTANT " << i << " ]" << endl;
        mutants[i].print();
    }
#endif

    return mutants;

}


vector<int> run(int numIterations);

    vector<int> getBest();


    vector<Individual> createMutants(int number);

    vector<Individual> rankIndividuals(vector<Individual> population);
    vector<Individual> assignFitness(vector<Individual> population);

    vector<Individual> createNewGeneration(vector<Individual> population);
    vector<Individual> getElite(vector<Individual> population);
    vector<Individual> getNormies(vector<Individual> population);

    vector<Individual> crossoverNormies(vector<Individual> elite, vector<Individual> normies, int numRemixed);

    Individual crossoverNormie(Individual elite, Individual normie);
