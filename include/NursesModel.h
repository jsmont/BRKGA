#ifndef __NURSES_MODEL__
#define __NURSES_MODEL__

#include "Brkga.h"

class NursesModel : virtual public FitnessModel {

    vector<int> demmand;
    int nNurses; 
    int nHours;
    int minHours;
    int maxHours;
    int maxConsec;
    int maxPresence;

public:
    NursesModel(int nNurses, int nHours, vector<int> demmand, int minHours, int maxHours, int maxConsec, int maxPresence);

    float getFitness(vector<float> chromosome);
    int getChromosomeLength();

    //Returns matrix of assigned[computer][task]
    vector<vector<bool> > decode(vector<float> chromosome);

    void printSolution(vector<float> chromosome);

private:

    int isFeasible(vector<vector<bool> > &partial_solution, int h, int n);
    vector<int> reorder(vector<float> weigths);
    void r_reorder(vector<float> &weigths, vector<int> &order, int begin, int end);

};

#endif
