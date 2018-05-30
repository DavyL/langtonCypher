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

	int ** timeList = malloc( listSize * sizeof(int *));
	
	struct antStruct * ant = malloc(sizeof(struct antStruct));
	ant->dir = 3;
	ant->x = 0;
	ant->y=0;	
	
	int currHeight = 0;
	int currWidth = 0;

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
			
			printf("Starting grid : %d x %d\n", currHeight, currWidth);

			if( blockSize > pow(2,currHeight * currWidth)){
				packet.blockSize = pow(2, currHeight * currWidth);
				printf("BlockSize is too large (%d > %d x %d ) , resizing it to %d \n", blockSize, currHeight, currWidth, packet.blockSize);	
			}else{
			 	packet.blockSize = blockSize;
			}			



			packet.height = currHeight;
			packet.width = currWidth;
	
			packet.binary = (int *) realloc(  packet.binary, currHeight * currWidth);

						
			i = 0;
			for(i = 0; i < listSize - 1; i++){

				timeList[i] = (int *) realloc(timeList[i], currHeight * currWidth);
				fillList(timeList[i], -1, currHeight, currWidth);
			}
			lastSent = (int *) realloc( lastSent, currHeight * currWidth);
			fillList(lastSent, -1, currHeight, currWidth);


			//copyList(lastSent, timeList[0], currHeight, currWidth);
			
			/*numElem = 0;
			if(numElem = numElemList(timeList, currHeight, currWidth, listSize - 1) > listSize/2){
				printf("Time list contains %d  elements, starting to clear it\n", numElem);	
				packet.binary = timeList[ extractElemFromTimeList(timeList, currHeight, currWidth, listSize) ];		
				sendToCli( packet ); 

			}else{ */
			
				printf("Time list contains %d elements\n", numElem);
				packet.binary = timeList[0];
				sendToCli( packet ); 
				binaryClock(timeList[0], currHeight * currWidth); 
				
				//addElem(timeList, packet.binary, currHeight, currWidth, listSize);

			//}

//		free_tree(packet.tree);	
//
//		free(ant);
//		
//		for(j = 0; j < listSize - 1; j++){
//			if(timeList[j] != NULL){
//				free(timeList[j]);
//			}else{
//				printf("Trying to free() timeList[%d], but it is a NULL pointer\n", j);
//			}
//		}
//		free(timeList);
	
		}
	}
	
}

int sendToCli(struct packetStruct packet){

	printf("Sending : ");
	displayBinary(packet.binary, packet.height, packet.width);
	printf(" to client\n");	
	mainCli(packet);

}


