#ifndef SERVER_H 
#define SERVER_H

#include "ant.h"

int mainServ(struct antStruct *, int, int, int, int);

struct packetStruct sendToCli(struct packetStruct );

#endif
