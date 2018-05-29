#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "analysis.h"
#include "arbres.h"
#include "ant.h"
#include "utils.h"
#include "client.h"

int mainCli( int * binary, struct antStruct * ant , int blockSize, int height, int width){

	printf("Entering mainCli() with ");
	displayBinary(binary, height, width);
	printf(" and a blocksize : %d\n", blockSize);

	t_abr timeTree = NULL;
	t_abr tempTree = NULL;

	int j = 0;

	timeTree = computeNLattice(ant, binary, blockSize, height, width);
		
	int * count = malloc(sizeof(int));
        *count = 0;	
	printf("Counter is %d \n", sumCounter( timeTree, count)); 
	printf("Number of equivalence class is %d \n", elemCounter( timeTree, count)); 
	printf("Number of equivalence class with multiplicity %d \n", sumProductCounter( timeTree, count)); 

	sendToServer(timeTree, binary, ant, blockSize, height, width);

	free(ant);
	free(binary);
	free_tree(timeTree);

	return 0;
}

int sendToServer(t_abr timeTree, int * binary, struct antStruct * ant, int blocksize, int height, int width){

	printf("The timeTree of the binary with a blocksize : %d has been sent to the server\n", blocksize);


	return 0;

}
