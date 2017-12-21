#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/* Parameters */
int nInstances = 100;
int minNurses = 100;
int maxNurses = 1000;
int total_hours = 24;
int minMinHours = 4;
int maxMinHours = 6;
int minMaxHours = 6;
int maxMaxHours = 12;
int minMaxConsec = 1;
int maxMaxConsec = 6;
int minMaxPresence;
int maxMaxPresence;
int demand_h[24];
float factorDemand = 0.7;
float factorConsec = 0.7;

/* Data of the instance */
int nNurses;
int minHours;
int maxHours;
int maxConsec;
int maxPresence;
time_t t;

void initialize_input() {
	int i=0;

	nNurses = (minNurses + rand() % (maxNurses - minNurses + 1));
	for (i = 0; i < total_hours; i++){
		demand_h[i] = rand() % ((int) (factorDemand * nNurses));
	}

	minHours = (minMinHours + rand() % (maxMinHours - minMinHours + 1));
	maxHours = (minMaxHours + rand() % (maxMaxHours - minMaxHours + 1));
	while (maxHours <= minHours)	/*maxHours must be greater than minHours*/
		maxHours = (minMaxHours + rand() % (maxMaxHours - minMaxHours + 1));

	maxConsec = (minMaxConsec + rand() % ((int) (factorConsec * maxHours)));
  while (maxConsec > maxHours)	/*maxConsec must be l.e. than maxHours */
		maxConsec = (minMaxConsec + rand() % ((int) (factorConsec * maxHours)));

	minMaxPresence = (((maxHours / maxConsec) * (maxConsec+1)) - 1 + (maxHours % maxConsec) + ((maxHours % maxConsec)!= 0)); /*maxPresence must be at least the case a nurse always works in consecutive hours*/
	maxMaxPresence = (maxHours * 2) - 1; /*maxPresence must be at most the case a nurse works 1 hour and rest 1 hour every time*/
	maxPresence = (minMaxPresence + rand() % (maxMaxPresence - minMaxPresence + 1));
  while (maxPresence > total_hours)	/*maxPresence must be l.e. than total_hours*/
		maxPresence = (minMaxPresence + rand() % (maxMaxPresence - minMaxPresence + 1));
}

void print(ofstream& file) {
	int i;
	file << nNurses << endl;
    file << total_hours << endl;
	for (i=0; i < total_hours; i++) 
		file << demand_h[i] << " ";
	file << minHours << endl;
	file << maxHours << endl;
	file << maxConsec << endl;
	file << maxPresence << endl;
}

int main() {
	int i=0;
	/*Intializes random number generator*/
	srand((unsigned) time(&t));

	/* Declaration of the files we will use */
	string name = "Nurse";
	ofstream outFile[nInstances];

	while (i < nInstances) {
		/* Open the file */
		outFile[i].open((name + to_string(i) + ".dat").c_str());
		
		/*Intializes the dependent problem variables*/
		initialize_input();
	
		/* Print the data into the file*/
		print(outFile[i]);
	
		/* Close the file */
		outFile[i].close();

		++i;
	}
}
