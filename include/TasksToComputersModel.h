#ifndef __TASKS_TO_COMPUTERS_MODEL__
#define __TASKS_TO_COMPUTERS_MODEL__

#include "Brkga.h"

class TasksToComputersModel : virtual public FitnessModel {

    vector<int> tasks;
    vector<int> computers;
    int total_resources; 
    int total_load;

public:
    TasksToComputersModel();

    float getFitness(vector<float> chromosome);
    int getChromosomeLength();

    //Returns matrix of assigned[computer][task]
    vector<vector<bool>> decode(vector<float> chromosome);

    void printSolution(vector<float> chromosome);

    void addTask(int resourcesUsed);
    void addComputer(int resources);

private:

    int findFeasibleAssignment(int task, vector<int> remainingLoad, vector<int> reorderComputers);

};

#endif
