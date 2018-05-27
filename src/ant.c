#include <stdio.h>
#include <stdlib.h>

#include "ant.h"

struct latticeStruct * newLattice(int height, int width, int color){		

	struct latticeStruct * lattice = malloc(sizeof(struct latticeStruct));
	
	lattice->height = height;
	lattice->width = width;
	
	if(color == -1 || color == 1){			//If clear is set to -1 or 1, then the grid will be filled with the value "clear"
							//Be careful, otherwise the grid will not be clearly defined
		
		lattice->grid = malloc(height * sizeof(int * ));
		
		int i = 0;
		int j = 0;
		if(lattice->grid){
			for( i = 0; i < lattice->height; i++){
				lattice->grid[i] = malloc( width * sizeof(int));
				if(lattice->grid[i]){
					for( j = 0; j < lattice->width; j++){
						lattice->grid[i][j] = color;		//-1 : white
											//+1 : black
					}
				}else
					printf("Couldn't allocate memory for lattice width :/\n");
			}
		}else
			printf("Couldn't allocate memory for lattice :/\n");
	}else
		printf("The grid is not properly defined");

	return lattice;

}


void * printBasics(struct antStruct * ant, struct latticeStruct * lattice){
	printf("Ant is at location : %d, %d, pointing towards : %d, on a case of color : %d\n", ant->x, ant->y, ant->dir, lattice->grid[ant->x][ant->y]);
}

void * displayGrid(struct latticeStruct * lattice){

	int i = 0;
	int j= 0;

	for( i = 0; i < lattice->height; i++){
		for( j = 0; j < lattice->width; j++){
			printf("%d",lattice->grid[i][j]);
		}
	printf("\n");
	}
}

void * direction(struct antStruct * ant, struct latticeStruct * lattice){	//Changes the color of the case on which the ant steps
	/*if (lattice->grid[ant->x][ant->y] == -1)
		ant->dir = mod(ant->dir - 1, 4);
	else
		ant->dir = mod(ant->dir + 1, 4);
	*/
	ant->dir = mod(ant->dir + lattice->grid[ant->x][ant->y], 4); 	//This is a shorter version of the above
									//The above is left in order to make code review easier :)
}

void * rvDirection(struct antStruct * ant, struct latticeStruct * lattice){	//reverse function of the direction
	ant->dir = mod(ant->dir - lattice->grid[ant->x][ant->y], 4); 
}


void * paint(struct antStruct * ant, struct latticeStruct * lattice){
	lattice->grid[ant->x][ant->y] = -lattice->grid[ant->x][ant->y];	//Changing the color of a case corresponds to multiplying it by -1
}


void * move(struct antStruct * ant, struct latticeStruct * lattice){

	switch ( ant->dir ){						//The ant goes where it is pointing
		case 0:
			ant->x = mod( ant->x + 1, lattice->height);
			break;
		case 1:
			ant->y = mod( ant->y + 1, lattice->width);
			break;
		case 2:
			ant->x = mod( ant->x - 1, lattice->height);
			break;
		case 3:
			ant->y = mod( ant->y - 1, lattice->width);
			break;
	}
}

void * rvMove(struct antStruct * ant, struct latticeStruct * lattice){

	switch ( ant->dir ){						//The ant goes opposite from where it is pointing
		case 0:
			ant->x = mod( ant->x - 1, lattice->height);
			break;
		case 1:
			ant->y = mod( ant->y - 1, lattice->width);
			break;
		case 2:
			ant->x = mod( ant->x + 1, lattice->height);
			break;
		case 3:
			ant->y = mod( ant->y + 1, lattice->width);
			break;
	}
}
int successor( struct antStruct * ant, struct latticeStruct * lattice, int n ){	//Computes n steps of langton's rule
	int i = 0;
	
	for( i = 0; i < n; i ++){
		move(ant, lattice);
		direction(ant, lattice);
		paint(ant, lattice);
	}
	
	return n;
}

int predecessor( struct antStruct * ant, struct latticeStruct * lattice, int n){
	
	int i = 0;	
	
	for( i = 0; i<n; i ++){
		paint(ant, lattice);
		rvDirection(ant, lattice);
		rvMove(ant, lattice);
	}
	
	return n;
}


