#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "analysis.h"
#include "ant.h"
#include "arbres.h"

int equivClassesCounter(int height, int width, int verbose){
	fprintf(stdout, "Computing %d x %d grids in equivClassesCounter()\n", height, width);
	struct antStruct * ant = malloc(sizeof(struct antStruct));
	ant->x = 0;
	ant->y = 0;
	ant->dir = 3;

	int * binary = malloc(height * width * sizeof(int)); 
	int i = 0;
	for(i = 0; i < height * width; i ++){
		binary[i] = -1;
	}
	
	t_abr * timeTree = malloc(sizeof(t_abr));
	*timeTree = NULL;
	t_abr * tempTree = malloc(sizeof(t_abr));
	*tempTree = NULL;
	int j = 0;

	//timeTree = computeNLattice(ant, binary, 1, height, width);
	int permNumb = pow(2, height*width);
	for(j=0; j < permNumb; j++){
		(*timeTree == NULL) ? (timeTree = computeNLattice(ant, binary, 1, height, width, verbose) ): (tempTree =computeNLattice(ant, binary, 1, height, width, verbose));
	 	merge_tree(tempTree, timeTree);
		free_tree(*tempTree);
		*tempTree = NULL;
	}
	
	//tree2dot(timeTree);
	//tree2tex(timeTree);
	
	int * count = malloc(sizeof(int));
        int * elem = malloc(sizeof(int));
	int * sumProd = malloc(sizeof(int));
	*count 	= 0;
	*elem 	= 0;
	*sumProd= 0;
	
	getTreeInfo(*timeTree, count, elem, sumProd);

	fprintf(stdout, "Counter is %d \n", *count);
	fprintf(stdout, "Number of equivalence class is %d \n", *elem); 
	fprintf(stdout, "Number of equivalence class with multiplicity %d \n", *sumProd); 

	free(count);
	free(elem);
	free(sumProd);
	
	free(ant);
	free(binary);
	free(count);
	free_tree(*timeTree);
	free_tree(*tempTree);
       
}

struct packetStruct computePacket( struct packetStruct packet, int verbose ){

	*packet.tree = *computeNLattice(packet.ant, packet.binary, packet.blockSize, packet.height, packet.width, verbose);
	return packet;
}


t_abr  * computeNLattice(struct antStruct * ant,int * binary, int n, int height, int width, int verbose){		//Computes n lattices starting from the binary

	t_abr * tempTimeTree = malloc(sizeof(t_abr));	
	*tempTimeTree = NULL;

	struct countStruct data;
	data.counter = 1;
	data.val = 0;

	struct latticeStruct * lattice = malloc(sizeof(struct latticeStruct));;

	int j = 0;
	
	if(verbose){
		fprintf(stdout, "Starting to compute %d lattice starting from : ", n);
		displayBinary( binary, height, width );
		printf("\n");
	}
	
	for(j = 0; j < n; ++j){
		if(verbose){
			fprintf(stdout, "Iteration number %d \t/\t %d\n", j, n);
		}
		
		lattice = listToLattice(binaryClock(binary, height * width),  height, width);
		data = 	periodFinder(ant, lattice);
		
		freeLattice(lattice);
	
		if(verbose){
			fprintf(stdout, "data val : %d, counter : %d\n", data.val, data.counter);
		
			if(*tempTimeTree == NULL){
				fprintf(stderr, "tempTimeTree is a NULL pointer\n");
			}
		}
		(*tempTimeTree == NULL ) ? (*tempTimeTree = new_abr(data, NULL, NULL)) : ajout_feuille(tempTimeTree, data); 
		
	}
	if(verbose){
		fprintf(stdout, "A whole block of size %d has been computed\n", n);
	}
	return tempTimeTree;
}

void computeAllPackets(int N, int M, int blockSize, int latex, int verbose){
	
	struct antStruct * ant = malloc(sizeof(struct antStruct));
	ant->dir 	= 0;
	ant->x		= 0;
	ant->y		= 0;

	int * count = malloc(sizeof(int));
        int * elem = malloc(sizeof(int));
	int * sumProd = malloc(sizeof(int));

	struct packetStruct *** packetList;
	packetList = createPacketList(N, M, blockSize);

	int height = 0;
	int width = 0;
	
	for(height = 1; height < N; height++){
		for(width = 1; width < M; width++){
		
		allocPacket(packetList[height][width]);
		packetList[height][width]->binary = fillList(packetList[height][width]->binary, -1, packetList[height][width]->height, packetList[height][width]->width);
	
		}
	}

	struct packetStruct * packetRcv;
	packetRcv 		= malloc(sizeof(struct packetStruct));
	packetRcv->ant	 	= malloc(sizeof(ant));
	packetRcv->ant->dir 	= 42;
	packetRcv->ant->x 	= 42;
	packetRcv->ant->y 	= 42;
	packetRcv->tree 	= malloc(sizeof(t_abr));
	*packetRcv->tree 	= NULL;	

	for(height = 1; height < N; height++){
		for(width = 1; width < M; width++){
	
			do{
				copyPacket(packetRcv ,sendToCli( packetList[height][width], verbose ));
					
				if(verbose){
					fprintf(stdout, "Received a packet\n");
				}


				packetList[height][width]->tree = merge_tree(packetRcv->tree, packetList[height][width]->tree);
				packetList[height][width]->binary = packetRcv->binary;
			
				if(verbose){
					fprintf(stdout, "Received binary :");
					displayBinary(packetRcv->binary, packetRcv->height, packetRcv->width);
					printf("\n");
				}
				
				free_tree(*packetRcv->tree);
				*packetRcv->tree = NULL;
			
			}while( !isEmpty(packetRcv->binary, packetRcv->height, packetRcv->width));
			
			packetList[height][width]->computed = 1;

			if(verbose){

				*count 	= 0;
				*elem 	= 0;
				*sumProd= 0;
				
				getTreeInfo(*(packetList[height][width]->tree), count, elem, sumProd);

				fprintf(stdout, "Counter is %d \n", *count);
				fprintf(stdout, "Number of equivalence class is %d \n", *elem); 
				fprintf(stdout, "Number of equivalence class with multiplicity %d \n", *sumProd);
			}
		}
	}

	extractData(packetList, N, M, latex); 


		if(latex){
//		tree2dot(*mainTree, packetSnd.height, packetSnd.width);
//		tree2tex(*mainTree, packetSnd.height, packetSnd.width);
	}
	
	/*free(packetSnd.ant);
	free(packetSnd.binary);
	free(packetSnd.tree);
*/
	for(height = 0; height < N; height++){
		for(width = 0; width < M; width++){
			
			freePacketContent( *(packetList[height][width]));
		}
	}

	free(packetRcv->ant);
	free(packetRcv->tree);

	free(elem);	
	free(sumProd);
	free(count);

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

	if(backupLattice == NULL || backupAnt == NULL){

		fprintf(stderr, "In periodFinder(), backupAnt and/or backupLattice are/is NULL pointer\n");

	}

	do{
		successor(ant, lattice, 1);
		(data.val)++;
	}while(compareGrids(lattice, backupLattice) || compareAnts(ant, backupAnt));
	
	freeLattice(backupLattice);
	free(backupAnt);
	
	return data;
}

struct antStruct * copyAnt(struct antStruct * ant){
	if (ant == NULL){
		fprintf(stderr, "In copyAnt, ant is a NULL pointer\n");
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
		fprintf(stderr, "In copyGrid, lattice is a NULL pointer\n");
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
		fprintf(stderr, "In compareAnts, one of the arguments is a NULL pointer\n");
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
		fprintf(stderr, "In compareGrids() one of the arguments is a NULL pointer\n");
		return 1;
	}


	if(lattice->height != latticeRef->height || lattice->width != latticeRef->width){
		fprintf(stderr, "In compareGrids the two lattices are not the same size\n");
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
			lattice = newLattice(i, j, 0);		//A random lattice is defined	

			successor(ant, lattice, 1);	
			fprintf(stdout, "The period of a %d x %d grid is %d\n", i, j, periodFinder(ant, lattice));
		
			freeLattice(lattice);
		}
	}
	free(ant);
}


