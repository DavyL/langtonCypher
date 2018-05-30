#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "ant.h"
#include "analysis.h"
#include "arbres.h"
#include "server.h"


int mod(int, int);

int main( int argc, char ** argv, char **envv){
	
	int i = 0;
	//equivClassesCounter(2, 2);
	
	int minHeight = 4;
	int minWidth  = 4;
	
	int maxHeight = 5;
	int maxWidth  = 5;

	int listSize 	= 10;
	int blockSize 	= 1024;

	mainServ(minHeight, minWidth, maxHeight, maxWidth, listSize, blockSize);
}



int mod(int a, int b){
	return (b + a)%b;			//returns the value we expect when computing a modulo, i.e : positive and < b
}
