#include<iostream>
#include <fstream>
#include <string>
using namespace std;
#include <sys/time.h>

#include "Brkga.h"
#include "NursesModel.h"

int main(int argc, char *argv[]){

    int populationSize = 40;
    int numElite = 5;
    int numNormies = 25;
    float ro = 0.7;

    int remainingIterations = 2000;

    ofstream iterative;
    ofstream overtime;


    iterative.open("iterations.csv", ios_base::app);
    overtime.open("time.csv", ios_base::app);


    iterative << endl << 0;
    overtime << endl << 0;

    struct timeval start, itime;

    gettimeofday(&start, NULL);

    for(int i = 1; i < argc-1; i+=2){

        switch(argv[i][0]){
            case 'p':
                cout << "POPULATION DEFINED TO " << atoi(argv[i+1]) << endl;
                populationSize=atoi(argv[i+1]);
                break;
            case 'e':
                cout << "ELITE DEFINED TO " << atoi(argv[i+1]) << endl;
                numElite=atoi(argv[i+1]);
                break;
            case 'n':
                cout << "NORMIES DEFINED TO " << atoi(argv[i+1]) << endl;
                numNormies=atoi(argv[i+1]);
                break;
            case 'i':
                cout << "ITERATIONS DEFINED TO " << atoi(argv[i+1]) << endl;
                remainingIterations=atoi(argv[i+1]);
                break;
            case 'r':
                cout << "RO DEFINED TO " << atof(argv[i+1]) << endl;
                ro=atof(argv[i+1]);
                break;
        }
    }

    int iteration = 0;
    int batch = remainingIterations/10000;
    if(batch == 0) batch = 1;

#ifdef EXAMPLE
    cout << "USING EXAMPLE MODEL" << endl;
    static const int arr[] = {40, 35, 31, 19, 12, 32, 1, 34, 2, 51};
    vector<int> demmand(arr, arr + sizeof(arr) / sizeof(arr[0]) );

    NursesModel model = NursesModel(150, demmand.size(), demmand, 2, 3, 2, 4);
#else

    cout << "LOADING MODEL FROM STDIN" << endl;
    int nNurses, nHours;
    cin >> nNurses >> nHours;

    vector<int> demmand = vector<int>(nHours);
    for(int i = 0; i < demmand.size(); ++i) cin >> demmand[i];

    int minHours, maxHours, maxConsec, maxPresence;

    cin >> minHours >> maxHours >> maxConsec >> maxPresence;

    NursesModel model = NursesModel(nNurses, nHours, demmand, minHours, maxHours, maxConsec, maxPresence);

    cout << "MODEL LOADED" << endl;

#endif

    cout << "TOTAL GENERATIONS " << remainingIterations << endl;

    Brkga instance = Brkga(populationSize, numElite, numNormies, ro, &model);

    cout << "STARTING EXECUTION" << endl;

    float fitness = instance.run(0);

    while (remainingIterations > batch){
        cout << "RUNNING GENERATION " << iteration << " WITH FITNESS " << fitness << " AND NURSES " << (int)fitness/100 <<  endl;

        gettimeofday(&itime, NULL);
        iterative << "; " <<(int)(fitness)/100;
        overtime << "; " << (itime.tv_sec - start.tv_sec); 


        fitness = instance.run(batch);

        remainingIterations-=batch;
        iteration+= batch;
    }
    cout << "RUNNING GENERATION " << iteration << " WITH FITNESS " << fitness << endl;
        gettimeofday(&itime, NULL);
        iterative << "; " << (int)fitness/100;
        overtime << "; " << (itime.tv_sec - start.tv_sec); 


    fitness = instance.run(remainingIterations);

    iteration += remainingIterations;
    cout << "RUNNING GENERATION " << iteration << " WITH FITNESS " << fitness << endl;
        gettimeofday(&itime, NULL);
        iterative << "; " << (int)fitness/100;
        overtime << "; " << (itime.tv_sec - start.tv_sec); 


    cout << "\rEXECUTION FINISHED." << endl;
    cout << "FINAL FITNESS " << fitness << endl;

    vector<float> bestChromosome = instance.getBest();

    model.printSolution(bestChromosome);

    iterative.close();
    overtime.close();
}

