#include "Brkga.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>

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

bool Individual::operator>(const Individual& other) const{
    return fitness < other.fitness;
}

Brkga::Brkga(int chromosomeLength, int populationSize, int numElite, int numNormies, float ro, FitnessFunction fitness){
    
    this->chromosomeLength = chromosomeLength;
    this->numElite = numElite;
    this->numNormies = numNormies;
    this->ro = ro;
    this->fitness = fitness;

    this->population = createMutants(populationSize);

    this->population = rankIndividuals(this->population);
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


float Brkga::run(int numIterations){
    
    for (int i = 0; i < numIterations; ++i){
    
        this->population = createNewGeneration(this->population);

        this->population = rankIndividuals(this->population);

#ifdef VITERATION
        cout << endl <<  "[VERBOSE ITERATION]" << endl;
        inspectPopulation(population);
#endif 
    }

    return getBestFitness(this->population);

}


vector<Individual> Brkga::rankIndividuals(vector<Individual> population){

    population = assignFitness(population);

    sort(population.begin(), population.end(), std::greater<>());

#ifdef VRANK
    cout << endl <<  "[VERBOSE RANK]" << endl;
    inspectPopulation(population);
#endif

    return population;
}

vector<Individual> Brkga::assignFitness(vector<Individual> population){

    for(int i = 0; i < population.size(); ++i){
    
        population[i].fitness = this->fitness(population[i].chromosome);

    }

#ifdef VFITNESS
    cout << endl <<  "[VERBOSE FITNESS]" << endl;
    inspectPopulation(population);
#endif 

    return population;

}

vector<Individual> Brkga::createNewGeneration(vector<Individual> population){

    return population;

}

/*
    vector<Individual> getElite(vector<Individual> population);
    vector<Individual> getNormies(vector<Individual> population);

    vector<Individual> crossoverNormies(vector<Individual> elite, vector<Individual> normies, int numRemixed);

    Individual crossoverNormie(Individual elite, Individual normie);
*/

float Brkga::getBestFitness(vector<Individual> population){

    return population[0].fitness;

}

vector<float> Brkga::getBest(){

    return this->population[0].chromosome;

}

void Brkga::inspectPopulation(vector<Individual> population){

    for(int i = 0; i < population.size(); ++i){
    
        cout << "[Individual " << i << " ]" << endl;

        population[i].print();

    }

}
