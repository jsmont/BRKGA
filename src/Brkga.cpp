#include "Brkga.h"
#include <iostream>
#include <algorithm>
#include <random>

Individual::Individual(){
    fitness = -1;
}

Individual::Individual(int chromosomeLength){
    chromosome = vector<float>(chromosomeLength);

    random_device rd;

    for(int i = 0; i < chromosome.size(); ++i){
        chromosome[i] = ((float)rd())/rd.max();
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

bool Individual::operator<(const Individual& other) const{
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

    vector<Individual> mutants = vector<Individual>(number);

    for(int i = 0; i < mutants.size(); ++i){
        mutants[i] = Individual(chromosomeLength);
    }


#ifdef VMUTANTS
    cout << endl << "[VERBOSE MUTANTS]" << endl;
    inspectPopulation(mutants);
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

    sort(population.begin(), population.end());

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
    cout << endl <<  "[ VERBOSE FITNESS]" << endl;
    inspectPopulation(population);
#endif 

    return population;

}

vector<Individual> Brkga::createNewGeneration(vector<Individual> population){

    vector<Individual> newPopulation = vector<Individual>(0);

    vector<Individual> elite = getElite(population);
    
    newPopulation.insert(newPopulation.end(), elite.begin(), elite.end());

    vector<Individual> normies = getNormies(population);

    vector<Individual> newNormies = crossoverNormies(elite, normies, numNormies);

    newPopulation.insert(newPopulation.end(), newNormies.begin(), newNormies.end());

    vector<Individual> mutants = createMutants(population.size() - numElite - numNormies);

    newPopulation.insert(newPopulation.end(), mutants.begin(), mutants.end());

#ifdef VGENERATION
    cout << endl << "[ VERBOSE GENERATION ]" << endl;
    inspectPopulation(newPopulation);
#endif

    return newPopulation;

}

vector<Individual> Brkga::getElite(vector<Individual> population){
    
    vector<Individual> elite = vector<Individual>(population.begin(), population.begin() + numElite);

#ifdef VELITE
    cout << endl << "[ VERBOSE ELITE ]" << endl;
    inspectPopulation(elite);
#endif
    
    return elite;

}

vector<Individual> Brkga::getNormies(vector<Individual> population){

    vector<Individual> normies = vector<Individual>(population.begin() + numElite, population.end());
    
#ifdef VNORMIES
    cout << endl << "[ VERBOSE NORMIES ]" << endl;
    inspectPopulation(normies);
#endif

    return normies;
}

vector<Individual> Brkga::crossoverNormies(vector<Individual> elite, vector<Individual> normies, int numRemixed){

    vector<Individual> remixedNormies = vector<Individual>(numRemixed);

    for(int i = 0; i < remixedNormies.size(); ++i){
    
        Individual selectedElite = elite[rand() % elite.size()];
        Individual selectedNormie = normies[rand() % normies.size()];

        remixedNormies[i] = crossoverNormie(selectedElite, selectedNormie);

    }

#ifdef VREMIXED
    cout << endl << "[ VERBOSE REMIXED ]" << endl;
    inspectPopulation(remixedNormies);
#endif
    return remixedNormies;

}

Individual Brkga::crossoverNormie(Individual elite, Individual normie){

    Individual remixed = Individual(chromosomeLength);

    for(int i = 0; i < remixed.chromosome.size(); ++i){
    
        remixed.chromosome[i] = normie.chromosome[i];

        if((((float)rand())/RAND_MAX) < ro){
            
            remixed.chromosome[i] = elite.chromosome[i];

        }
    }

    return remixed;
}

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
