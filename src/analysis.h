#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "ant.h"

struct countStruct{
	
	int value;
	int counter;

};

int compareGrids(struct latticeStruct * lattice, struct latticeStruct * latticeRef);
int compareAnts(struct antStruct * ant, struct antStruct * antRef);

struct antStruct * copyAnt(struct antStruct *);
struct latticeStruct * copyLattice(struct latticeStruct * lattice);

int periodicFinder(struct antStruct *, struct latticeStruct *);

int sizeAnalysis( int, int );	

#endif
