#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#include "ant.h"
#include "analysis.h"
#include "arbres.h"
#include "server.h"


int mod(int, int);

int main( int argc, char ** argv, char **envv){
	
		
	int i = 0;
	//equivClassesCounter(2, 2);
	
	struct antStruct * ant = malloc(sizeof(ant));
	ant->dir 	= 0;
	ant->x		= 0;
	ant->y		= 0;
	int height 	= 3;
	int width 	= 3;
	int listSize 	= 10;
	int blockSize 	= 1024;
	
	int j = 0;
	while ((j = getopt(argc, argv, "h:w:l:b:")) != -1) {
		switch (j) {
		case 'h':
			height = atoi(optarg); 
			break;
		case 'w':
			width = atoi(optarg);
			break;
		case 'l':
			listSize = atoi(optarg);
			break;
		case 'b':
			blockSize = atoi(optarg);
			break;
		}
	}

	mainServ(ant, height, width, listSize, blockSize);
}



int mod(int a, int b){
	return (b + a)%b;			//returns the value we expect when computing a modulo, i.e : positive and < b
}
