#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "ant.h"

struct countStruct{
	
	int value;
	int counter;

};

int equivClassesCounter(int, int);

int * binaryClock(int * , int );
struct latticeStruct * listToLattice(int * list, int, int );

int compareGrids(struct latticeStruct * , struct latticeStruct * );
int compareAnts(struct antStruct * , struct antStruct * );

struct antStruct * copyAnt(struct antStruct *);
struct latticeStruct * copyLattice(struct latticeStruct * );

int periodFinder(struct antStruct *, struct latticeStruct *);

int sizeAnalysis( int, int );	

#endif
