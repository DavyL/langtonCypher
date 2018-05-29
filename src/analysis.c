#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "analysis.h"
#include "ant.h"
#include "arbres.h"

int equivClassesCounter(int height, int width){
	struct antStruct * ant = malloc(sizeof(struct antStruct));
	ant->x = 0;
	ant->y = 0;
	ant->dir = 3;

	int * binary = malloc(height * width * sizeof(int)); 
	int i = 0;
	for(i = 0; i < height * width; i ++){
		binary[i] = -1;
	}
	
	t_abr timeTree = NULL;

	int j = 0;
	int permNumb = pow(2, height*width);
	
	timeTree = *computeNLattice(&timeTree, ant, binary, permNumb, height, width);

	tree2dot(timeTree);
	tree2tex(timeTree);
	
	int count = 0; 
	printf("Counter is %d \n", sumCounter( timeTree, count)); 

	free(ant);
	free(binary);
	free_tree(timeTree);

       
}

t_abr * computeNLattice(t_abr * timeTree, struct antStruct * ant,int * binary, int n, int height, int width){		//Computes n lattices starting from the binary
	
	int j = 0;
	for(j = 0; j < n; j++){
		printf("Iteration number %d \t/\t %d\n", j, j);
		ajout_feuille( timeTree, periodFinder(ant, listToLattice(binaryClock(binary, height * width),  height, width))); 	
	}
	return timeTree;
}


int * binaryClock(int * clock, int clockSize){
	int i = 0;
	for( i = 0; i< clockSize ; i++){
		if(clock[i] == -1){
			clock[i] = 1;
			return clock;
		}
		clock[i] = -1;
	}
	return clock;
}

struct latticeStruct * listToLattice(int * list, int height, int width){	//list contains a list of -1 and 1
												//listToLattice() returns the corrresponding lattice
	int listSize = height * width;
	
	struct latticeStruct * lattice = newLattice(height, width, -1);
	
	int i = 0;
	int j = 0;
	for(i = 0; i < listSize ; i++){
		lattice->grid[i%height][i/height] = list[i];
	}

	return lattice;
}                                                                           


struct countStruct periodFinder(struct antStruct * ant, struct latticeStruct * lattice){
	struct countStruct data;
	data.val = 0;
	data.counter = 1;
	
	struct latticeStruct * backupLattice = copyLattice(lattice);
	struct antStruct * backupAnt = copyAnt(ant);

	do{
		successor(ant, lattice, 1);
		data.val++;
	}while(compareGrids(lattice, backupLattice) || compareAnts(ant, backupAnt));
	
	free(backupLattice);
	free(backupAnt);
	
	return data;
}

struct antStruct * copyAnt(struct antStruct * ant){
	if (ant == NULL){
		printf("In copyAnt, ant is a NULL pointer\n");
		return NULL;
	}
	
	struct antStruct * copy = malloc(sizeof(struct antStruct));
	
	copy->x = ant->x;
	copy->y = ant->y;
	copy->dir = ant->dir;

	return copy;

}

struct latticeStruct * copyLattice(struct latticeStruct * lattice){
	if(lattice == NULL){
		printf("In copyGrid, lattice is a NULL pointer\n");
		return NULL;
	}
	
	struct latticeStruct * copy = newLattice(lattice->height, lattice->width, -1);
	
	int i = 0;
	int j = 0;
	for(i = 0; i < lattice->height ; i ++){
		for(j = 0; j < lattice->width ; j++){
			copy->grid[i][j] = lattice->grid[i][j]; 
		}
	}

	return copy;

}

int compareAnts(struct antStruct * ant, struct antStruct * antRef){				//returns 0 if ant and antRef contain the same elements 
												//1 otherwise	
	if(ant == NULL || antRef == NULL){
		printf("In compareAnts, one of the arguments is a NULL pointer\n");
		return 1;
	}	
	if(ant->dir != antRef->dir || ant->x != antRef->x || ant->y != antRef->y){
		return 1;
	}
	return 0;


}

int compareGrids(struct latticeStruct * lattice, struct latticeStruct * latticeRef){		//returns 0 if lattice and lattice ref contain the same elements
												//1 otherwise
	int i = 0;
	int j = 0;

	if(lattice == NULL || latticeRef == NULL){
		printf("In compareGrids() one of the arguments is a NULL pointer\n");
		return 1;
	}


	if(lattice->height != latticeRef->height || lattice->width != latticeRef->width){
		printf("In compareGrids the two lattices are not the same size\n");
		return 1;
	}


	for(i = 0; i< lattice->height; i++){
		for(j = 0; j<lattice->width; j++){
			if( lattice->grid[i][j] != latticeRef->grid[i][j] ){
				return 1;
			}
		}
	}
	return 0;


}

int sizeAnalysis( int maxSize, int color ){				//Prints the size of the loops with increasing size	

	struct latticeStruct * lattice;

	struct antStruct * ant = malloc(sizeof( struct antStruct));;
	ant->x = 0;
	ant->y = 0;
	ant->dir = 3;			//The ant starts at the origin, pointing towards the top

	int i = 0;
	int j = 0;
	for(i = 1; i < maxSize; i++){
		for(j = 1; j <= i; j++){
			lattice = newLattice(i, j, 0);		//A (white) lattice is defined	

			successor(ant, lattice, 1);	
			printf("The period of a %d x %d grid is %d\n", i, j, periodFinder(ant, lattice));
		
			free(lattice);
		}
	}
	free(ant);
}
