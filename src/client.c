#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "struct.h"
#include "analysis.h"
#include "arbres.h"
#include "ant.h"
#include "utils.h"
#include "client.h"

struct packetStruct * mainCli( struct packetStruct * packet, int verbose){
	if(packet->binary != NULL){
		if(verbose){	
			fprintf(stdout, "Entering mainCli() on a %d x %d grid, a blocksize : %d, and starting at : ", packet->height, packet->width, packet->blockSize);
			displayBinary(packet->binary, packet->height, packet->width);
			fprintf(stdout, "\n");
		}else{
			fprintf(stdout, "Entering mainCli() computing packet number  %d\t ( %f )\t on a %dx%d grid\n", binaryToDecimal(packet->binary), binaryToDecimal(packet->binary)/pow(2, packet->height * packet->width), packet->height, packet->width); 
		}
	}else{
		fprintf(stderr, "Packet received contained a NULL pointer inside binary\n");
		return packet;
	}
	packet->tree = computeNLattice( packet->ant, packet->binary, packet->blockSize , packet->height, packet->width, verbose);
		
	return packet;
}

int sendToServer( struct packetStruct packet){

	printf("The timeTree of the binary with a blocksize : %d and size !: %d x %d has been sent to the server\n", packet.blockSize, packet.height, packet.width);



	return 0;

}
