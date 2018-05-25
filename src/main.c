#include <stdlib.h>
#include <stdio.h>

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
void * direction(struct antStruct * ant, struct latticeStruct * lattice);
void * paint(struct antStruct *, struct latticeStruct *);
void * move( struct antStruct *, struct latticeStruct *);
int successor( struct antStruct *, struct latticeStruct *, int );

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
	
	successor(&ant, &lattice, 10000);
}

void * printBasics(struct antStruct * ant, struct latticeStruct * lattice){
	printf("Ant is at location : %d, %d, pointing towards : %d, on a case of color : %d\n", ant->x, ant->y, ant->dir, lattice->grid[ant->x][ant->y]);
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

int mod(int a, int b){
	return (b + a)%b;			//returns the value we expect when computing a modulo, i.e : positive and < b
}
