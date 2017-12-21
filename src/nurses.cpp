#include<iostream>
using namespace std;

#include "Brkga.h"
#include "NursesModel.h"

int main(){

    int populationSize = 40;
    int numElite = 5;
    int numNormies = 25;
    float ro = 0.7;

    int remainingIterations = 20000;
    int batch = remainingIterations/10000;
    if(batch == 0) batch = 1;

#ifdef EXAMPLE
    static const int arr[] = {40, 35, 31, 19, 12, 32, 1, 34, 2, 51};
    vector<int> demmand(arr, arr + sizeof(arr) / sizeof(arr[0]) );

    NursesModel model = NursesModel(150, demmand.size(), demmand, 2, 3, 2, 4);
#else

    int nNurses, nHours;
    cin >> nNurses >> nHours;

    vector<int> demmand = vector<int>(nHours);
    for(int i = 0; i < demmand.size(); ++i) cin >> demmand[i];

    int minHours, maxHours, maxConsec, maxPresence;

    cin >> minHours >> maxHours >> maxConsec >> maxPresence;

    NursesModel model = NursesModel(nNurses, nHours, demmand, minHours, maxHours, maxConsec, maxPresence);

#endif

    Brkga instance = Brkga(populationSize, numElite, numNormies, ro, &model);

    while (remainingIterations > batch){
        float fitness = instance.run(batch);
        cout << "Remaining iterations: " << remainingIterations << "\tFitness: " << fitness << endl;
        remainingIterations-=batch;
    }

    float fitness = instance.run(remainingIterations);
    cout << "Remaining iterations: 0\tFitness: " << fitness << endl;

    vector<float> bestChromosome = instance.getBest();

    //Brkga::printChromosome(bestChromosome);

    model.printSolution(bestChromosome);
}
