#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "ant.h"

#define HEIGHT 100
#define WIDTH 100

int mod(int, int);

int main( int argc, char ** argv, char **envv){

	struct latticeStruct * lattice = newLattice(HEIGHT, WIDTH, -1);		//A (white) lattice is defined	

	struct antStruct * ant = malloc(sizeof( struct antStruct));;
	ant->x = 0;
	ant->y = 0;
	ant->dir = 3;			//The ant starts at the origin, pointing towards the top
	
	printBasics(ant, lattice);
	successor(ant, lattice, 1000);
	predecessor(ant, lattice, 1000);
	printBasics(ant, lattice);
}



int mod(int a, int b){
	return (b + a)%b;			//returns the value we expect when computing a modulo, i.e : positive and < b
}
