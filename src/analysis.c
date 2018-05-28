#include <stdio.h>
#include <stdlib.h>

#include "analysis.h"
#include "ant.h"

#define HEIGHT 5
#define WIDTH 5

int equivClassesCounter(){
	struct antStruct * ant = newLattice(HEIGHT, WIDTH, -1);




}

struct latticeStruct * binaryToLattice(int binary){


	return lattice;
}                                                                           

int ** listToListOfList(int * list, int divisor){


	return listOfList;
}


int periodicFinder(struct antStruct * ant, struct latticeStruct * lattice){
	int count = 0;
	
	struct latticeStruct * backupLattice = copyLattice(lattice);
	struct antStruct * backupAnt = copyAnt(ant);

	do{
		successor(ant, lattice, 1);
		count++;
	}while(compareGrids(lattice, backupLattice) || compareAnts(ant, backupAnt));
	
	free(backupLattice);
	free(backupAnt);
	
	return count;
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
			printf("The period of a %d x %d grid is %d\n", i, j, periodicFinder(ant, lattice));
		
			free(lattice);
		}
	}
	free(ant);
}
