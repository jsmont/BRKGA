#include "TasksToComputersModel.h"

#include <iostream>
using namespace std;

void printVector(vector<int> v){

    cout << "[ ";
    if(v.size() > 0) {
        cout << v[0];
        for(int i = 1; i < v.size(); ++i){
            cout << ",\t" << v[i] ;
        }
    }

    cout << " ]"<<endl;

}

TasksToComputersModel::TasksToComputersModel(){
    tasks = vector<int>(0);
    computers = vector<int>(0);
    total_resources= 0;
    total_load = 0;
}

void TasksToComputersModel::addTask(int resourcesUsed){
    
    tasks.push_back(resourcesUsed);
    total_load += resourcesUsed;

}

void TasksToComputersModel::addComputer(int resources){
    
    computers.push_back(resources);
    total_resources += resources;

}

int TasksToComputersModel::getChromosomeLength(){

    return computers.size() + tasks.size();

}

float TasksToComputersModel::getFitness(vector<float> chromosome){

    vector<vector<bool>> solution = decode(chromosome);

    float fitness = 0;

    for(int i = 0; i < solution.size(); ++i){
    
        int load = 0;
        for(int j = 0; j < solution[i].size(); ++j){

            if(solution[i][j])
                load += tasks[j];
        }

        if(load != 0){
            fitness += total_resources;
            fitness += computers[i] - load;
        }

    }

    for(int i = 0; i < solution[0].size(); ++i){
        bool assigned = false;
        for(int j = 0; j < solution.size() && !assigned; ++j){
            assigned |= solution[j][i];
        }

        if(!assigned){
            fitness += total_load;
        }

    }

    return fitness;

}

vector<vector<bool>> TasksToComputersModel::decode(vector<float> chromosome){

    vector<vector<bool>> assignments = vector<vector<bool>>(computers.size(), vector<bool>(tasks.size(), false));

    vector<int> remainingTasks = vector<int>(tasks.size());
    for(int i = 0; i < tasks.size(); ++i) remainingTasks[i] = i;

    vector<int> remainingLoad = computers;
    
    vector<int> remainingComputers = computers;
    vector<int> reorderComputers = vector<int>(computers.size());

    for(int i = 0; i < computers.size(); ++i) remainingComputers[i] = i;


    for(int i = 0; i < computers.size(); ++i){
    
        int selectedComputer = (int)((float)chromosome[i] * (float)remainingComputers.size());
        reorderComputers[i] = remainingComputers[selectedComputer];
        remainingComputers.erase(remainingComputers.begin()+selectedComputer);

    }

    cout << "[REORDER VECTOR]" << endl; 

    printVector(reorderComputers);

    for(int i = computers.size(); i < computers.size() + tasks.size(); ++i){

        int selectedTask = (int)((float)chromosome[i] * (float)remainingTasks.size());

        int task = remainingTasks[selectedTask];

        remainingTasks.erase(remainingTasks.begin() + selectedTask);

        int c = findFeasibleAssignment(tasks[task], remainingLoad, reorderComputers);

        if(c >= 0){
            remainingLoad[c] -= tasks[task];
            assignments[c][task] = true;
        }
    }

    return assignments;
}

int TasksToComputersModel::findFeasibleAssignment(int task, vector<int> remainingLoad, vector<int> reorderComputers){

    int i;
    for(i = 0; i < reorderComputers.size() && task > remainingLoad[reorderComputers[i]]; ++i);

    if(i == remainingLoad.size()) return -1;

    return reorderComputers[i];
}

void TasksToComputersModel::printSolution(vector<float> chromosome){

    cout << endl << "[ SOLUTION ]" << endl;

    cout << "[TASKS]" << endl;
    for( int i = 0; i < tasks.size(); ++i){
        cout << i << ": " << tasks[i] << "\t";
    }

    cout << endl;

    cout << "[COMPUTERS]" << endl;
    for(int i = 0; i < computers.size(); ++i){
        cout << i << ": " << computers[i] << "\t";
    }

    cout << endl;

    cout << "[ASSIGNMENTS]" << endl;


    vector <int> computer_loads = vector<int>(computers.size(), 0);

    vector<vector<bool>> solution = decode(chromosome);

    for( int i = 0; i < solution.size(); ++i){
    
        cout << "Computer " << i << ":";
        for(int j = 0; j < solution[i].size(); ++j){
            if(solution[i][j]) {
                cout << "\t" << j;
                computer_loads[i] += tasks[j];
            }
        }
        cout << endl;
    }

    cout << endl;
    cout << "[COMPUTER LOADS]" << endl;

    for(int i = 0; i < computers.size(); ++i){
        cout << "Computer " << i << ": " << 100.0*(float)computer_loads[i]/(float)computers[i] << " %" << endl;
    }
}
