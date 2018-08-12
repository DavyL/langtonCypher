#ifndef CLIENT_H
#define CLIENT_H

//#include "struct.h"

struct packetStruct * mainCli( struct packetStruct *, int );

int sendToServer( struct packetStruct );

#endif
