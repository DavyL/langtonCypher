#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "server.h"
#include "arbres.h"
#include "ant.h"
#include "analysis.h"

#define LIST_SIZE 10
#define BLOCK_SIZE 1024
int mainServ(){

	printf("Entering mainServ()\n");

	int height = 4;
	int width = 4;

	int blockSize= BLOCK_SIZE;

	int ** timeList = malloc( LIST_SIZE * sizeof(int *));
	int * lastSent = malloc(height * width * sizeof(int));

	int numElem = 0;
	
	int i = 0;
	for(i = 0; i < LIST_SIZE; i++){

		timeList[i] = malloc( height * width * sizeof(int));
		fillList(timeList[i], -1, height, width);
	}
	


	if(numElem = numElemList(timeList, height, width) > LIST_SIZE/2){
		printf("Time list contains %d  elements, starting to clear it\n", numElem);	
		sendToCli( timeList[ extractElemFromTimeList(timeList, height, width) ], height, width, blockSize); 

	}else{
		printf("Time list contains %d elements\n", numElem);
		lastSent = binaryClock(copyList(NULL, timeList[0], height, width), blockSize);
		sendToCli(lastSent, height, width, blockSize); 
		addElem(timeList, lastSent, height, width);

	}
}

int sendToCli(int * binary, int height, int width, int blockSize){

	printf("The binary \t");
	int i = 0;
	for(i = 0; i < height*width; i ++){
	
		printf(" %d ", binary[i]);

	}
	printf(" has been sent to the client with a blocksize : %d \n", blockSize);

}

int numElemList( int ** timeList, int height, int width){		//Returns the number of non-zero elem in timeList

	int i = 0;
	int numberOfElem = LIST_SIZE ;
	for(i = 0; i < LIST_SIZE ; i++){
		numberOfElem -= isEmpty(timeList[i], height, width);
	}
	return numberOfElem;
}

int extractElemFromTimeList(int ** timeList, int height, int width){ 	//Returns the position of a non-zero elem from timeList

	int i = 0;
	for(i = 0; i < LIST_SIZE; i++){
		if(!isEmpty(timeList[i], height, width)){
			return i;
		}
	}
}

int * popElemFromTimeList(int ** timeList, int height, int width){	//pops timeLst[0] and shifts the other elements
	int * temp = malloc( height * width * sizeof(int));
	int i = 0;
	temp = timeList[0];
	for( i = 0; i < LIST_SIZE  - 1; i++){

		copyList(timeList[i], timeList[i + 1], height, width);

	}
	fillList( timeList[LIST_SIZE - 1], -1, height, width);
	return temp;
}

int * fillList(int * binary, int val, int height, int width){

	int i = 0;
	for(i = 0; i < height * width; i ++){
		binary[i] = val;
	}

	return binary;

}

int * addElem(int ** timeList, int * elem, int height, int width){

	int i = 0;
	for(i = 0; i < LIST_SIZE; i ++){
		if( isEmpty(timeList[i], height, width) ){
			timeList[i] = elem;
		}
	}
}


int * copyList( int * list1, int * list2, int height, int width){	//Moves elements from list2 to list 1
									//returns the address of list2
	
	if(list1 == NULL){						//If list1 is a NULL pointer, copyList() returns a pointer to a copy of list2
	
		list1 = malloc(height * width * sizeof(int));
		return copyList(list1, list2, height, width);

	}

	int i = 0;
	for(i= 0; i <height * width; i++){
		list1[i] = list2[i];
	}

	return list2;
}

int isEmpty( int * binary, int height, int width){		//returns 1 if the list is empty, i.e, contains only -1

	int i = 0;
	for( i = 0; i < height * width; i ++){

		if(binary[i] != -1){
			return 0;
		}
	}
	return 1;
}

int displayTimeList( int ** timeList, int height, int width){

	int i = 0;
	for(i = 0; i < LIST_SIZE ; i++){
		displayBinary(timeList[i], height, width);
		printf("\n");
	}
	return 0;
}

int displayBinary(int * binary, int height, int width){
	int i = 0;
	for(i = 0; i < height * width; i ++){
		printf("%d", binary[i]);
	}
	return 0;
}


