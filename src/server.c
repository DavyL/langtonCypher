#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "server.h"
#include "arbres.h"
#include "ant.h"
#include "analysis.h"
#include "utils.h"

#define LIST_SIZE 10
#define BLOCK_SIZE 1024
int mainServ(int listSize, int blockSize){

	printf("Entering mainServ()\n");

	struct antStruct * ant = malloc(sizeof(struct antStruct));
	ant->dir = 3;
	ant->x = 0;
	ant->y=0;	
	
	int height = 4;
	int width = 4;

	int ** timeList = malloc( listSize * sizeof(int *));
	int * lastSent = malloc(height * width * sizeof(int));

	t_abr timeTree = NULL;

	int numElem = 0;
	
	int i = 0;
	for(i = 0; i < listSize; i++){

		timeList[i] = malloc( height * width * sizeof(int));
		fillList(timeList[i], -1, height, width);
	}
	


	if(numElem = numElemList(timeList, height, width, listSize) > listSize/2){
		printf("Time list contains %d  elements, starting to clear it\n", numElem);	
		sendToCli( timeList[ extractElemFromTimeList(timeList, height, width, listSize) ], ant, blockSize, height, width); 

	}else{
		printf("Time list contains %d elements\n", numElem);
		lastSent = binaryClock(copyList(NULL, timeList[0], height, width), blockSize);
		sendToCli(lastSent, ant, blockSize, height, width); 
		addElem(timeList, lastSent, height, width, listSize);

	}
}

int sendToCli(int * binary, struct antStruct * ant, int blockSize, int height, int width){

	printf("Sending : ");
	displayBinary(binary, height, width);
	printf(" to client\n");	
	mainCli(binary, ant, blockSize, height, width);

}


