#include<iostream>
using namespace std;

#include "Brkga.h"
#include "TasksToComputersModel.h"

int main(){
    
    int populationSize = 5;
    int numElite = 2;
    int numNormies = 2;
    float ro = 0.7;

    int remainingIterations = 10;
    int batch = remainingIterations/100;
    if(batch == 0) batch = 1;

    TasksToComputersModel model = TasksToComputersModel();

    model.addTask(500);
    model.addTask(200);
    model.addTask(300);

    model.addComputer(700);
    model.addComputer(200);
    model.addComputer(300);

    Brkga instance = Brkga(populationSize, numElite, numNormies, ro, &model);

    while (remainingIterations > batch){
        float fitness = instance.run(batch);
        cout << "Remaining iterations: " << remainingIterations << "\tFitness: " << fitness << endl;
        remainingIterations-=batch;
    }

    float fitness = instance.run(remainingIterations);
    cout << "Remaining iterations: 0\tFitness: " << fitness << endl;

    vector<float> bestChromosome = instance.getBest();

    Brkga::printChromosome(bestChromosome);

    model.printSolution(bestChromosome);
}
