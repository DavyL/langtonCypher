#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "struct.h"
#include "ant.h"
#include "arbres.h"


int equivClassesCounter(int, int);

int * binaryClock(int * , int );
struct latticeStruct * listToLattice(int * list, int, int );

struct packetStruct computePacket( struct packetStruct );
t_abr computeNLattice(struct antStruct * , int *, int, int, int);

int compareGrids(struct latticeStruct * , struct latticeStruct * );
int compareAnts(struct antStruct * , struct antStruct * );

struct antStruct * copyAnt(struct antStruct *);
struct latticeStruct * copyLattice(struct latticeStruct * );

struct countStruct  periodFinder(struct antStruct *, struct latticeStruct *);

int sizeAnalysis( int, int );	

#endif
