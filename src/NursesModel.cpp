#include "NursesModel.h"

#include <iostream>
#include <cmath>
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

void printVector(vector<float> v){

    cout << "[ ";
    if(v.size() > 0) {
        cout << v[0];
        for(int i = 1; i < v.size(); ++i){
            cout << ",\t" << v[i] ;
        }
    }

    cout << " ]"<<endl;

}
void printVector(vector<bool> v){

    cout << "[ ";
    if(v.size() > 0) {
        cout << (int)v[0];
        for(int i = 1; i < v.size(); ++i){
            cout << ",\t" << (int)v[i] ;
        }
    }

    cout << " ]"<<endl;

}



NursesModel::NursesModel(int nNurses, int nHours, vector<int> demmand, int minHours, int maxHours, int maxConsec, int maxPresence){

    this->demmand = demmand;
    this->nNurses = nNurses;
    this->nHours = nHours;
    this->minHours = minHours;
    this->maxHours = maxHours;
    this->maxConsec = maxConsec;
    this->maxPresence = maxPresence;

}

float NursesModel::getFitness(vector<float> chromosome){

    vector<vector<bool> > solution = decode(chromosome);
    vector<int> nworks = vector<int>(nNurses, 0);
    int nursesUsed = 0;
    int satisfiedHours = 0;

    for(int i = 0; i < solution.size(); ++i){
        int count = 0;
        for(int j = 0; j < solution[i].size(); ++j){
            if(solution[i][j]){
                count++;
                nursesUsed += (nworks[j]==0);
                nworks[j]++;
            }
        }

        satisfiedHours += (count >= demmand[i]);

    }


    float avg = 0;
    for(int i = 0; i < nworks.size(); ++i){
        avg += ((float)nworks[i])/(float)nursesUsed;
    }

    float sq_sum = 0;

    for(int i = 0; i < nworks.size(); ++i){
        if(nworks[i] != 0)
            sq_sum += (nworks[i] - avg)*(nworks[i] - avg);
    }

    float std = sq_sum/nursesUsed;

    float max_std = (maxHours/2)*(maxHours/2);

    float normalized_std = std/max_std;

    return 100*(1-normalized_std) + 100*(nursesUsed + nNurses*(nHours - satisfiedHours));

}

int NursesModel::getChromosomeLength(){
    return nHours + nHours*nNurses;
}

//Returns matrix of assigned[computer][task]
vector<vector<bool> > NursesModel::decode(vector<float> chromosome){

    vector<vector<bool> > partial_solution = vector<vector<bool> >(nHours, vector<bool>(nNurses, false));

    vector<float> reorderHoursWeigths(chromosome.begin(), chromosome.begin()+nHours);
    chromosome.erase(chromosome.begin(), chromosome.begin()+nHours);

    vector<int> reorderHours = reorder(reorderHoursWeigths);

#ifdef DDECODE
    cout << "[ VERBOSE DECODE ]" << endl;
    cout << "HOUR ORDER: ";
    printVector(reorderHours);
#endif

    vector<vector<int> > reorderNurses(nHours);

    for(int i = 0; i < nHours; ++i){

        vector<float> reorderNursesWeights(chromosome.begin()+(nNurses*i), chromosome.begin()+(nNurses*(i+1)));

        reorderNurses[i] = reorder(reorderNursesWeights);
    }

    for(int i = 0; i < nHours; ++i){
        int h = reorderHours[i];

        int requiredNurses = demmand[h];
#ifdef DDECODE
        cout << "Building hour " << h << endl;
        cout << "NURSES ORDER: ";
        printVector(reorderNurses[h]);
#endif

        for(int j = 0; j < nNurses && (requiredNurses > 0); ++j){

            int n = reorderNurses[h][j];

            if(isFeasible(partial_solution, h, n)){
                partial_solution[h][n] = true;
                requiredNurses--;
            }
        }
        //cout << "H: " << h << "\tD: " << demmand[h]  << "\tS: "<< requiredNurses << endl;
    }

    return partial_solution;

}

void NursesModel::printSolution(vector<float> chromosome){

    vector <vector<bool> > solution = decode(chromosome);


    for(int h = 0; h < nHours; ++h){
        cout << "\t" << h;
    }
    cout << endl;

    vector <int> count = vector<int>(nHours, 0);
    for(int n = 0; n < nNurses; ++n){
        cout << n << "|";
        for(int h  = 0; h < solution.size(); ++h){
            if(solution[h][n]){
                cout << "\t" << 1;
                count[h]++;
            } else {
                cout << "\t" << 0;
            }
        }
        cout << endl;
    }

    for(int i = 0; i < nHours; ++i){
        cout << "\t" << count[i];
    }

    cout << endl;
    cout << endl << "Fitness: " << getFitness(chromosome) << endl;
    cout << endl << "Nurses used: " << (int)getFitness(chromosome)/100 << endl;

}

#ifdef DFEASIBLE
#define CONTROL(s) \
    if( !feasible ) {\
        cout << "maxPresence: " << maxPresence << "\tmaxHours: " << maxHours <<  "\tmaxConsec: " << maxConsec << endl;\
        cout << "Presence: " << presence << "\ttotalHours: " << totalHours << "\tinvalidRests: " << invalidRests << endl;\
        cout << s << endl;\
        partial_solution[h][n] = false;\
        return feasible;\
    }
#else
#define CONTROL(s)
#endif

int NursesModel::isFeasible(vector<vector<bool> > &partial_solution, int h, int n){

    bool feasible = true;

    partial_solution[h][n] = true;

#ifdef DFEASIBLE
    cout << endl << "[ VERBOSE FEASIBLE ]" << endl;
    cout << "Hour: " << h << " Nurse: " << n << endl;
    vector <bool> nurse_status = vector<bool>(nHours);
    for(int i = 0; i < nHours; ++i) nurse_status[i] = partial_solution[i][n];
    printVector(nurse_status);
#endif

    int totalHours = 0;
    int consecHours = 0;
    int firstHour = -1;
    int lastHour = -1;
    int presence = 0;
    int invalidRests = 0;

    for(int i = 0; i < nHours && feasible; ++i){

        totalHours += (partial_solution[i][n] == true);

        consecHours += (partial_solution[i][n] == true);

        if(partial_solution[i][n]){

            if(firstHour == -1) firstHour = i;
            lastHour = i;

        } else {
            consecHours = 0;
        }

        feasible &= (consecHours <= maxConsec);
        CONTROL("INVALID CONSEC HOURS");
    }

    feasible &= (totalHours <= maxHours);

    CONTROL("INVALID TOTAL HOURS");

    presence = lastHour - firstHour +1;
    feasible &= (presence <= maxPresence);

    CONTROL("INVALID PRESENCE HOURS");

    if(presence > totalHours){
        int partial = 0;
        for(int i = firstHour+1; i < lastHour && feasible; ++i){

            if(partial_solution[i][n] == false && partial_solution[i-1][n] == false)
                partial++;
            else if(partial != 0) {
                if(partial_solution[i-1][n] == false){

                    int consecHours = 1;
                    for(int j = i; j <= lastHour && partial_solution[j][n]; ++j)
                        consecHours++;
                    if(consecHours > maxConsec) feasible = false;

                }
                invalidRests += (partial+1)/2;
                partial = 0;
            }

        }

        CONTROL("INVALID REST + CONSEC HOURS")

        feasible &= (invalidRests <= (maxHours - totalHours));
        CONTROL("INVALID REST HOURS V1");

    }

#ifdef DFEASIBLE
    if(feasible){
        cout << "VALID" << endl;
    }
#endif
    partial_solution[h][n] = false;

    return feasible;

}

vector<int> NursesModel::reorder(vector<float> weigths){

    vector<int> order = vector<int>(weigths.size(), 0);
    for(int i = 0; i < order.size(); ++i) order[i] = i;

#ifdef DREORDER
    cout << endl << "REORDERING" << endl;
    printVector(weigths);
#endif

    r_reorder(weigths, order, 0, order.size());

#ifdef DREORDER

    cout << "[ VERBOSE REORDER ]" << endl;  
    printVector(weigths);
    printVector(order);

#endif 

    return order;
}

void NursesModel::r_reorder(vector<float> &weigths, vector<int> &order, int begin, int end){

    int length = end-begin;
    if(length > 1){


        int half = begin + length/2;

#ifdef DREORDER
        cout << "FROM " << begin << "-" << end << " -> Calling " << begin << "-" << half << endl;
#endif
        r_reorder(weigths, order, begin, half);
#ifdef DREORDER
        cout << "FROM " << begin << "-" << end << " -> Calling " << half << "-" << end << endl;
#endif
        r_reorder(weigths, order, half, end);

        vector<int> reordered = vector<int>(length,0);

        for(int k=0, i = begin, j = half; k < length; ++k){

            if(i == half){
                reordered[k] = order[j];
                j++;
            } else if (j == end) {
                reordered[k] = order[i];
                i++;
            } else if(weigths[order[i]] > weigths[order[j]]){
                reordered[k] = order[j];
                j++;
            } else {
                reordered[k] = order[i];
                i++;
            }

        }

#ifdef DREORDER
        cout << "Begin: " << begin << " End: " << end << endl;
        printVector(reordered);
#endif
        for(int i = 0; i < length; ++i){
            order[begin + i] = reordered[i];
        }

    }

}
