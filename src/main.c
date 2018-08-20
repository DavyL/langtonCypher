#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#include "ant.h"
#include "analysis.h"
#include "arbres.h"
#include "server.h"


int mod(int, int);
void print_usage();

void print_usage()
{

	fprintf(stdout, "Options:\n");
	fprintf(stdout, " -h 		\t display this help and exit\n");
	fprintf(stdout, " -W <int>	\t Set width of the grid to <int>\n");
	fprintf(stdout, " -H <int>	\t Set height of the grid to <int>\n");
	fprintf(stdout, " -l <int> 	\t Set listSize to <int>, not used yet\n");
	fprintf(stdout, " -b <int>  	\t Set the blockSize to <int>, i.e. the size of the blocks tha twill be sent to clients, default 1024\n \t\t\t BlockSize must divide 2^height*width, otherwise, blockSize will be set to 2^height*width\n");
	fprintf(stdout, " -t <int>	\t If int != 0, the program will extract a graphic version of the tree, default = 1\n");
	fprintf(stdout, "\n");
}
int main( int argc, char ** argv, char **envv){
	
		
	int i = 0;

	struct antStruct * ant = malloc(sizeof(struct antStruct));
	ant->dir 	= 0;
	ant->x		= 0;
	ant->y		= 0;
	int height 	= 3;
	int width 	= 3;

	int latex 	= 0;		//Boolean value, if latex == 1 a .tex file (and it's pdf) will
					//be produced by the program representing the timeTree

	int listSize 	= 10;
	int blockSize 	= 1024;		//Size of the blocks used in computation
	
	int N	= 4;			//Size of the list to be computed on the serv
	int M 	= 4;


	int j = 0;
	
	int autoMode = 0;		//boolean value, if autoMode == 1 then the program will use
					//equivClassesCounter() instead of the block computation
	
	int verbose = 0;		//boolean value, if verbose == 1, program is in verbose mode

	int compAll = 0;		//Used to compute all packets locally, only here for testing reasons
	while ((j = getopt(argc, argv, "N:M:H:W:l:b:t:heva")) != -1) {
		switch (j) {
		case 'N':
			N = atoi(optarg);
			break;
		case 'M':
			M = atoi(optarg);
			break;
		case 'H':
			height = atoi(optarg); 
			break;
		case 'W':
			width = atoi(optarg);
			break;
		case 'l':
			listSize = atoi(optarg);
			break;
		case 'b':
			blockSize = atoi(optarg);
			break;
		case 't':
			latex = atoi(optarg);
			break;
		case 'e':
			autoMode = 1;
			break;
		case 'v':
			verbose = 1;
			break;
		case 'a':
			compAll = 1;
			break;
		case 'h':
			print_usage();
			return EXIT_SUCCESS;
		}
	}
	if(N <= height){
		fprintf(stderr, "ERROR. Check the size of the server list\n");
		fprintf(stderr, "Values : N = %d\t height = %d\n", N, height);
		return EXIT_FAILURE;
	}
	if(M <= width){	
		fprintf(stderr, "ERROR. Check the size of the server list\n");
		fprintf(stderr, "Values : M = %d\t width = %d\n", M, width);
		return EXIT_FAILURE;
	}
	if(compAll){
		computeAllPackets( N, M, blockSize, latex, verbose);
		return EXIT_SUCCESS;
	}

	if(autoMode){
		equivClassesCounter(height, width, verbose);
		return EXIT_SUCCESS;
	}else{
		mainServ(ant, N, M, height, width, listSize, blockSize, latex, verbose);
		return EXIT_SUCCESS;
	}
	free(ant);
}



int mod(int a, int b){
	return (b + a)%b;			//returns the value we expect when computing a modulo, i.e : positive and < b
}
