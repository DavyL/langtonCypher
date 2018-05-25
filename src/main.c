#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define HEIGHT 100
#define WIDTH 100

struct antStruct {
	unsigned int x;
	unsigned int y;
	int dir;
};
struct latticeStruct {
	int grid[HEIGHT][WIDTH];
	int height;
	int width;
};

void * printBasics(struct antStruct *, struct latticeStruct *);
void * displayGrid(struct latticeStruct * lattice);
void * direction(struct antStruct * ant, struct latticeStruct * lattice);
void * paint(struct antStruct *, struct latticeStruct *);
void * move( struct antStruct *, struct latticeStruct *);
int successor( struct antStruct *, struct latticeStruct *, int );


long long decimalToBinary(long long  );
long long binaryToDecimal(long long  );

int * numberToArray(long long);
  
int * textToBinArray( char *);

int mod(int, int);

int main( int argc, char ** argv, char **envv){

	struct latticeStruct lattice;
	lattice.height = HEIGHT;
	lattice.width = WIDTH;	
	
	int i = 0;
	int j = 0;

	for( i = 0; i < lattice.height; i++){
		for( j = 0; j < lattice.width; j++){
			lattice.grid[i][j] = -1;		//-1 : white
								//+1 : black
		}
	}

	struct antStruct ant;
	ant.x = 0;
	ant.y = 0;
	ant.dir = 3;					//The ant starts at the origin, pointing towards the top
	
	char * sentence = "Hello World";	
	int numSentence = (int)(sentence);
	printf("numsentence = %d\n", numSentence);
	numSentence = decimalToBinary( numSentence);
	printf("numsentence = %d\n", numSentence);
	

}

void * printBasics(struct antStruct * ant, struct latticeStruct * lattice){
	printf("Ant is at location : %d, %d, pointing towards : %d, on a case of color : %d\n", ant->x, ant->y, ant->dir, lattice->grid[ant->x][ant->y]);
}

void * displayGrid(struct latticeStruct * lattice){
	int i = 0;
	int j= 0;

	for( i = 0; i < lattice->height; i++){
		for( j = 0; j < lattice->width; j++){
			printf("%d",lattice->grid[i][j]);
		}
	printf("\n");
	}
}

void * direction(struct antStruct * ant, struct latticeStruct * lattice){	//Changes the color of the case on which the ant steps
	/*if (lattice->grid[ant->x][ant->y] == -1)
		ant->dir = mod(ant->dir - 1, 4);
	else
		ant->dir = mod(ant->dir + 1, 4);
	*/
	ant->dir = mod(ant->dir + lattice->grid[ant->x][ant->y], 4); 	//This is a shorter version of the above
									//The above is left in order to make code review easier :)
}

void * paint(struct antStruct * ant, struct latticeStruct * lattice){
	lattice->grid[ant->x][ant->y] = -lattice->grid[ant->x][ant->y];	//Changing the color of a case corresponds to multiplying it by -1
}


void * move(struct antStruct * ant, struct latticeStruct * lattice){
	switch ( ant->dir ){						//The ant goes where it is pointing
		case 0:
			ant->x = mod( ant->x + 1, lattice->height);
			break;
		case 1:
			ant->y = mod( ant->y + 1, lattice->width);
			break;
		case 2:
			ant->x = mod( ant->y - 1, lattice->height);
			break;
		case 3:
			ant->y = mod( ant->y - 1, lattice->width);
			break;
	}
}

int successor( struct antStruct * ant, struct latticeStruct * lattice, int n ){	//Computes n steps of langton's rule
	int i = 0;
	for( i = 0; i < n; i ++){
		move(ant, lattice);
		direction(ant, lattice);
		paint(ant, lattice);
	}
	return n;
}

long long decimalToBinary(long long decimal){
	int i = 0;
	long long binary = 0;
	int remainder = 0;
	//int step = 0;
	for( i = 1; decimal != 0; i *= 10){
	        remainder = decimal%2;
            	decimal /= 2;
        	binary += i*remainder;
    	}				
	return binary;
}



long long binaryToDecimal(long long binary){
	int i = 0;
	long long decimal = 0;
	int remainder = 0;
	for( i =  1; binary != 0; i*= 2){
		remainder = binary%10;
		binary /= 10;
		decimal += i*remainder;
	}
	return decimal;
}

int * numberToArray(long long number){
	int i = 0;
	int length = (int) (log10((float) number)) + 1;
	int * array = (int *) malloc(length * sizeof(int));
	for(i = length; i != 0 ; number /= 10, --i){
		array[i] = number%10;
	}
	return array;
}

int * textToBinArray( char * text){
	return numberToArray(decimalToBinary((int) text ));
}

int mod(int a, int b){
	return (b + a)%b;			//returns the value we expect when computing a modulo, i.e : positive and < b
}
