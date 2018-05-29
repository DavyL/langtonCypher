#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "ant.h"
#include "analysis.h"
#include "arbres.h"
#include "server.h"

#define HEIGHT 5
#define WIDTH 5

int mod(int, int);

int main( int argc, char ** argv, char **envv){
	
	int i = 0;
	//equivClassesCounter(2, 2);
	mainServ( 10, 1024);
}



int mod(int a, int b){
	return (b + a)%b;			//returns the value we expect when computing a modulo, i.e : positive and < b
}
