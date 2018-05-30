#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "analysis.h"
#include "arbres.h"
#include "ant.h"
#include "utils.h"
#include "client.h"

int mainCli( struct packetStruct packet){

	printf("Entering mainCli() with ");
	displayBinary(packet.binary, packet.height, packet.width);
	printf(" and a blocksize : %d\n", packet.blockSize);

	packet.tree = NULL;

	int j = 0;

	packet = computePacket( packet );
		
	int * sum = malloc(sizeof(int));
	int * elem = malloc(sizeof(int));
	int * sumProduct = malloc(sizeof(int));
        *sum = 0;	
	*elem = 0;
	*sumProduct = 0;

	printf("Counter is %d \n", sumCounter( packet.tree, sum)); 
	printf("Number of equivalence class is %d \n", elemCounter( packet.tree, elem)); 
	printf("Number of equivalence class with multiplicity %d \n", sumProductCounter( packet.tree, sumProduct)); 

	sendToServer( packet);

	free(packet.ant);
	free(packet.binary);
	free_tree(packet.tree);

	free(sum);
	free(elem);
	free(sumProduct);

	printf("Leaving mainCli()\n");

	return 0;
}

int sendToServer( struct packetStruct packet){

	printf("The timeTree of the binary with a blocksize : %d and size !: %d x %d has been sent to the server\n", packet.blockSize, packet.height, packet.width);


	return 0;

}
