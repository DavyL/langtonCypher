#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "struct.h"
#include "server.h"
#include "arbres.h"
#include "ant.h"
#include "analysis.h"
#include "utils.h"

int mainServ(int minHeight, int minWidth, int maxHeight, int maxWidth, int listSize, int blockSize){

	printf("Entering mainServ()\n");

	struct antStruct * ant = malloc(sizeof(struct antStruct));
	ant->dir = 3;
	ant->x = 0;
	ant->y=0;	
	
	int currHeight = 0;
	int currWidth = 0;

	int ** timeList = NULL;

	int numElem = 0;
	int i = 0;
	
	int j = 0;

	int * count = malloc(sizeof(int));
	*count = 0;

	struct packetStruct packet;
	
	packet.listSize = listSize;
	packet.ant = ant;
	packet.tree = NULL;
	packet.binary = NULL;

	int * lastSent = NULL;

	for(currHeight = minHeight; currHeight <= maxHeight; currHeight ++){
		for( currWidth = minWidth; currWidth <= currHeight; currWidth ++){
			
			lastSent = malloc(currWidth * currHeight * sizeof(int));
	
			fillList(lastSent, -1, currHeight, currWidth);

			if( blockSize > pow(2,currHeight * currWidth)){

				packet.blockSize = pow(2, currHeight * currWidth);
				printf("BlockSize is too large (%d > %d x %d ) , resizing it to %d \n", blockSize, currHeight, currWidth, packet.blockSize);	
			}else{
			 	packet.blockSize = blockSize;
			}


			printf("Starting grid : %d x %d\n", currHeight, currWidth);			

			packet.height = currHeight;
			packet.width = currWidth;

			timeList = malloc( listSize * sizeof(int *));
			packet.binary = malloc( currHeight * currWidth * sizeof(int));

			numElem = 0;
			
			i = 0;
			for(i = 0; i < listSize - 1; i++){

				timeList[i] = malloc( currHeight * currWidth * sizeof(int));
				fillList(timeList[i], -1, currHeight, currWidth);
			}
	
			//copyList(lastSent, timeList[0], currHeight, currWidth);

			if(numElem = numElemList(timeList, currHeight, currWidth, listSize - 1) > listSize/2){
				printf("Time list contains %d  elements, starting to clear it\n", numElem);	
				packet.binary = timeList[ extractElemFromTimeList(timeList, currHeight, currWidth, listSize) ];		
				sendToCli( packet ); 

			}else{
				printf("Time list contains %d elements\n", numElem);
				lastSent = copyList(NULL, timeList[0], currHeight, currWidth), packet.blockSize;
				addElem(timeList, lastSent, currHeight, currWidth, listSize);
				packet.binary = lastSent;
				sendToCli( packet ); 
				
				//addElem(timeList, packet.binary, currHeight, currWidth, listSize);

			}
	
		printf("The grid  of size : %d x %d has been computed\n", currHeight, currWidth);
		printf("Counter is %d \n", sumCounter( packet.tree, count)); 
		printf("Number of equivalence class is %d \n", elemCounter( packet.tree, count)); 
		printf("Number of equivalence class with multiplicity %d \n", sumProductCounter( packet.tree, count));


		
		if(lastSent != NULL){
			free(lastSent);
		}

		free_tree(packet.tree);	

		free(ant);
		
		for(j = 0; j < listSize; j++){
			if(timeList[j] != NULL){
				free(timeList[j]);
			}else{
				printf("Trying to free() timeList[%d], but it is a NULL pointer\n", j);
			}
		}
		free(timeList);
	
		}
	}
}

int sendToCli(struct packetStruct packet){

	printf("Sending : ");
	displayBinary(packet.binary, packet.height, packet.width);
	printf(" to client\n");	
	mainCli(packet);

}


