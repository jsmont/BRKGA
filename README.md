# BRKGA
A simple implementation of the Biased Random-Key Genetic Algorithm in C++

This repository contains the main library for the algorithm on files:
  + include/Brkga.h
  + src/Brkga.cpp
 
And also three diferent models for three diferent problems:
  + Dummy problem used as an example at class.
  + Assignment of Tasks to Computers explained in class.
  + Scheduling of nurses, which was the main project.
  
Also, it includes several instances known to be feasible on the instances folder.

## Compilation of nurses

In order to compile the problem you must run:

`make nurses CC=g++`

Where CC must be defined as your g++-7 compiler. You can not include the parameter if you use `g++-7`.

## Execution

The basic structure for exectuion is:

`./nurses [OPTIONS] < path_to_instance_file`

Where options can be:
  + **i**: to define the number of iterations
  + **p**: to define the size of the population
  + **e**: to define the amount of elite individuals (note that this is an integer value, not a proportion).
  + **n**: to define the amount of normies (instances produced by crossover at each generation).
  + **r**: to define the ro parameter (the chance a gene is inherited from the elite or from the source chromosome) (this is a float between 0-1).

An example of an execution using 100 iterations, a population size of 150, 37 elite individuals, 67 normies and a ro of 0.7, running with instance 'example.dat' would be:

`./nurses i 100 p 150 e 37 n 67 r 0.7 < example.dat`
