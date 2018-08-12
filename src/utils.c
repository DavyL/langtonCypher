#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int numElemList( int ** timeList, int height, int width, int listSize){		//Returns the number of non-zero elem in timeList

	int i = 0;
	int numberOfElem = listSize ;
	for(i = 0; i < listSize ; i++){
		numberOfElem -= isEmpty(timeList[i], height, width);
	}
	return numberOfElem;
}

int extractElemFromTimeList(int ** timeList, int height, int width, int listSize){ 	//Returns the position of a non-zero elem from timeList

	if(timeList == NULL){
		printf("In extractElemFromTimeList(), timeList is a NULL pointer\n");
		return -1;

	}
	int i = 0;
	for(i = 0; i < listSize; i++){
		if(timeList[i] == NULL){
			printf("In extractElemFromTimeList(), timeList[%d] is a NULL pointer\n", i);
			return -1;
		}
		if(!isEmpty(timeList[i], height, width)){
			return i;
		}
	}
}

int * popElemFromTimeList(int ** timeList, int height, int width, int listSize){	//pops timeLst[0] and shifts the other elements
	int * temp = malloc( height * width * sizeof(int));
	int i = 0;
	temp = timeList[0];
	for( i = 0; i < listSize  - 1; i++){

		copyList(timeList[i], timeList[i + 1], height, width);

	}
	fillList( timeList[listSize - 1], -1, height, width);
	return temp;
}

int * fillList(int * binary, int val, int height, int width){

	if(binary == NULL){
		printf("In fillList(), the binary is a NULL pointer\n");
		return NULL;
	}
	
	
	int i = 0;
	for(i = 0; i < height * width; i ++){
		binary[i] = val;
	}

	return binary;

}

int * addElem(int ** timeList, int * elem, int height, int width, int listSize){

	int i = 0;
	for(i = 0; i < listSize; i ++){
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

	return list1;
}

int isEmpty( int * binary, int height, int width){		//returns 1 if the list is empty, i.e, contains only -1

	if( binary == NULL){

		printf("In isEmpty(), the binary is a NULL pointer\n");
		return -1;

	}

	int i = 0;
	for( i = 0; i < height * width; i ++){

		if(binary[i] != -1){
			return 0;
		}
	}
	return 1;
}

int displayTimeList( int ** timeList, int height, int width, int listSize){

	int i = 0;
	for(i = 0; i < listSize ; i++){
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

