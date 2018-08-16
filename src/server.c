#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "struct.h"
#include "server.h"
#include "arbres.h"
#include "ant.h"
#include "analysis.h"
#include "utils.h"

#include "client.h"

int mainServ(struct antStruct * ant, int N, int M, int height, int width, int listSize, int blockSize, int latex, int verbose){

	fprintf(stdout, "Entering mainServ() on a %d x %d grid, list size : %d, blocksize : %d\n", height, width, listSize, blockSize);	

	/*struct packetStruct packetSnd;
	packetSnd.height 	= height;
	packetSnd.width 	= width;
	packetSnd.listSize 	= listSize;
	packetSnd.blockSize 	= blockSizeCheck(packetSnd.height, packetSnd.width, blockSize);
	packetSnd.ant 		= malloc(sizeof(ant));
	packetSnd.ant->dir 	= ant->dir;
	packetSnd.ant->x 	= ant->x;
	packetSnd.ant->y 	= ant->y;
	packetSnd.binary 	= malloc( packetSnd.height * packetSnd.width * sizeof(int));
	packetSnd.binary 	= fillList( packetSnd.binary, -1, packetSnd.height, packetSnd.width);
	packetSnd.tree 		= malloc(sizeof(t_abr));
	*packetSnd.tree		= NULL;	
	*/

	
	struct packetStruct *** packetList;
	packetList = createPacketList(N, M, blockSize);
	
	allocPacket((packetList)[height][width]);
	packetList[height][width]->binary = fillList(packetList[height][width]->binary, -1, packetList[height][width]->height, packetList[height][width]->width);
	


	struct packetStruct * packetRcv;
	packetRcv 		= malloc(sizeof(struct packetStruct));
	packetRcv->ant	 	= malloc(sizeof(ant));
	packetRcv->ant->dir 	= 42;
	packetRcv->ant->x 	= 42;
	packetRcv->ant->y 	= 42;
	packetRcv->tree 	= malloc(sizeof(t_abr));
	*packetRcv->tree 	= NULL;	

	t_abr * mainTree 	= malloc(sizeof(t_abr));
	*mainTree 		= NULL;

	do{
		copyPacket(packetRcv ,sendToCli( packetList[height][width], verbose ));
			
		if(verbose){
			fprintf(stdout, "Received a packet\n");
		}


		mainTree = merge_tree(packetRcv->tree, mainTree);
		packetList[height][width]->binary = packetRcv->binary;
	
		if(verbose){
			fprintf(stdout, "Received binary :");
			displayBinary(packetRcv->binary, packetRcv->height, packetRcv->width);
			printf("\n");
		}
		
		free_tree(*packetRcv->tree);
		*packetRcv->tree = NULL;
		free_tree(*(packetList[height][width]->tree));
		*(packetList[height][width]->tree) = NULL;
	
	}while( !isEmpty(packetRcv->binary, packetRcv->height, packetRcv->width));

	int * count = malloc(sizeof(int));
        int * elem = malloc(sizeof(int));
	int * sumProd = malloc(sizeof(int));
	*count 	= 0;
	*elem 	= 0;
	*sumProd= 0;
	
	getTreeInfo(*mainTree, count, elem, sumProd);

	fprintf(stdout, "Counter is %d \n", *count);
	fprintf(stdout, "Number of equivalence class is %d \n", *elem); 
	fprintf(stdout, "Number of equivalence class with multiplicity %d \n", *sumProd);
	
	if(latex){
//		tree2dot(*mainTree, packetSnd.height, packetSnd.width);
//		tree2tex(*mainTree, packetSnd.height, packetSnd.width);
	}
	
	/*free(packetSnd.ant);
	free(packetSnd.binary);
	free(packetSnd.tree);
*/
	freePacketContent( *packetList[height][width]);

	free(packetRcv->ant);
	free(packetRcv->tree);

	free(elem);	
	free(sumProd);
	free(count);

	free_tree(*mainTree);
	free(mainTree);

}

struct packetStruct *** createPacketList(int N, int M, int blockSize){

	int i = 0;
	int j = 0;

	struct packetStruct *** packetList;
	packetList = malloc(N*sizeof(struct packetStruct **));


	for(i = 0; i < N; i++){
		packetList[i] = malloc(M*sizeof(struct packetStruct *));
		for(j=0; j < M; j++){
			(packetList[i][j]) = malloc(sizeof(struct packetStruct));
			(packetList[i][j])->height 	= i;
			(packetList[i][j])->width 	= j;

			(packetList[i][j])->listSize 	= -1;
			(packetList[i][j])->blockSize 	= blockSizeCheck(i, j, blockSize);

			(packetList[i][j])->ant 	= NULL;

			(packetList[i][j])->binary 	= NULL; 
			
			(packetList[i][j])->tree 	= NULL;
			
			(packetList[i][j])->computed 	= 0;
			(packetList[i][j])->locked	= 0;
		}

	}

	return packetList;


}

void allocPacket( struct packetStruct * packet ){
	if(packet->ant == NULL){
		packet->ant 	= malloc(sizeof(struct antStruct));
		
		packet->ant->dir = 0;
		packet->ant->x 	= 0;
		packet->ant->y	= 0;
	}
	if(packet->binary == NULL){
		packet->binary 	= malloc(sizeof(int) * packet->height * packet->width);
	}
	if(packet->tree == NULL){
		packet->tree 	= malloc(sizeof(t_abr));
		*packet->tree	= NULL;
	}
}

void freePacketContent( struct packetStruct packet){		//Free the elements that use memory allocated with malloc() inside a packet

	free(packet.ant);
	free(packet.binary);
	free_tree(*packet.tree);

}


int blockSizeCheck(int height, int width, int blockSize){

	int maxSize = pow(2, height * width);

	if(blockSize > maxSize){
		fprintf(stderr, "Resizing blockSize (too large )from : %d to : %d\n", blockSize, maxSize);
		return maxSize;
	}else if(maxSize%blockSize != 0){
		fprintf(stderr, "blockSize %d is not a divider of maxSize : %d\n", blockSize, maxSize);
		return maxSize;
	}
	return blockSize;

}


struct packetStruct * sendToCli(struct packetStruct * packet, int verbose){

	if(verbose){
		fprintf(stdout, "Sending : ");
		displayBinary(packet->binary, packet->height, packet->width);
		fprintf(stdout, " to client\n");
	}
	
	return   mainCli(packet, verbose);


}

struct packetStruct * copyPacket( struct packetStruct * pack1, struct packetStruct * ptrPack){		//Copy value from ptrPack to pack1

	if(pack1 == NULL){
		pack1 = malloc(sizeof(struct packetStruct));
	}
	if(pack1->ant == NULL){
		pack1->ant = malloc(sizeof(struct antStruct));
	}
	if(pack1->tree == NULL){
		pack1->tree = malloc(sizeof(t_abr));
		*pack1->tree = NULL;
	}

	pack1->height 		= ptrPack->height;
	pack1->width 		= ptrPack->width;
	pack1->listSize 	= ptrPack->listSize;
	pack1->blockSize 	= ptrPack->blockSize;
	pack1->ant->dir 	= ptrPack->ant->dir;
	pack1->ant->x 		= ptrPack->ant->x;
	pack1->ant->y 		= ptrPack->ant->y;
	pack1->binary 		= copyList(pack1->binary, ptrPack->binary, ptrPack->height, ptrPack->width);
	//add copyTree(), i.e: merge_tree(pack1->tree, ptrPack->tree);	

	if(pack1->tree != NULL){
		free_tree(*pack1->tree);
		*pack1->tree = NULL;
	}
	pack1->tree	 = merge_tree(ptrPack->tree, pack1->tree);

	return pack1;
}

