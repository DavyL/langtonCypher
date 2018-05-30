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

int mainServ(struct antStruct * ant, int height, int width, int listSize, int blockSize){

	printf("Entering mainServ() on a %d x %d grid, list size : %d, blocksize : %d\n", height, width, listSize, blockSize);	

	struct packetStruct packetSnd;
	packetSnd.height 	= height;
	packetSnd.width 	= width;
	packetSnd.listSize 	= listSize;
	packetSnd.blockSize 	= blockSize;
	packetSnd.ant 		= malloc(sizeof(ant));
	packetSnd.ant->dir 	= ant->dir;
	packetSnd.ant->x 	= ant->x;
	packetSnd.ant->y 	= ant->y;
	packetSnd.binary 	= malloc( packetSnd.height * packetSnd.width * sizeof(int));
	packetSnd.binary 	= fillList( packetSnd.binary, -1, packetSnd.height, packetSnd.width);
	
	struct packetStruct packetRcv;
	packetRcv.ant	 	= malloc(sizeof(ant));


	t_abr mainTree = NULL;

	do{
		packetRcv = sendToCli( packetSnd );
		merge_tree(packetRcv.tree, &mainTree);
	}while( !isEmpty(packetRcv.binary, packetRcv.height, packetRcv.width));

	int * count = malloc(sizeof(int));
        int * elem = malloc(sizeof(int));
	int * sumProd = malloc(sizeof(int));
	*count 	= 0;
	*elem 	= 0;
	*sumProd= 0;	
	printf("Counter is %d \n", sumCounter( mainTree, count)); 
	printf("Number of equivalence class is %d \n", elemCounter( mainTree, elem)); 
	printf("Number of equivalence class with multiplicity %d \n", sumProductCounter( mainTree, sumProd)); 

	tree2dot(mainTree);
	tree2tex(mainTree);



}

struct packetStruct sendToCli(struct packetStruct packet){

	printf("Sending : ");
	displayBinary(packet.binary, packet.height, packet.width);
	printf(" to client\n");
	packet = (mainCli(packet));
	return   packet;


}


