#ifndef SERVER_H 
#define SERVER_H

//#include "ant.h"

int mainServ(struct antStruct *, int, int, int, int, int, int, int, int);

struct packetStruct * sendToCli(struct packetStruct *, int );

struct packetStruct *** createPacketList(int, int, int);

void extractData(struct packetStruct ***, int, int, int);

void extractDataFromPacket( struct packetStruct, int);
void saveTreeData( FILE *, t_abr);

void allocPacket(struct packetStruct *, int);
void freePacketContent( struct packetStruct);

struct packetStruct * copyPacket( struct packetStruct * pack1, struct packetStruct * ptrPack);

#endif
