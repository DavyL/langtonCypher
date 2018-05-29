#ifndef SERVER_H 
#define SERVER_H

int mainServ();

int sendToCli(int * , int , int , int );

int numElemList( int ** , int , int );

int extractElemFromTimeList(int ** , int , int );
int * popElemFromTimeList(int ** , int , int );
int * fillList(int * , int , int , int );
int * addElem(int ** , int *, int, int );

int * copyList( int * , int * , int , int );
int isEmpty( int * , int , int );

int displayTimeList( int ** , int, int );
int displayBinary(int *, int , int );
#endif
