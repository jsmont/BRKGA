#include "Brkga.h"
#include <cstdlib>
#include<stdio>

Individual::Individual(int chromosomeLength){
    chromosome = vector<float>(chromosomeLength);

    //std::random_device rand;

    for(int i = 0; i < chromosome.size(); ++i){
        chromosome[i] = ((float)rand())/RAND_MAX;//((float)rand())/rand.max();
    }

    fitness = -1;
}

Individual::print(){
    
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

    vector<Individual> mutants = vector<Individual>(number,chromosomeLength);

#ifdef VCREATEMUTANTS

    cout << endl << "[VERBOSE MUTANT CREATION]" << endl;

    for(int i = 0; i < mutants.size(); ++i)
        cout << "[MUTANT " << i << " ]" << endl;
        mutants[i].print();
#endif

    return mutants;

}
