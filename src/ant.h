#ifndef ANT_H
#define ANT_H

struct antStruct {
	unsigned int x;
	unsigned int y;
	int dir;
};
struct latticeStruct {
	int ** grid;
	int height;
	int width;
};

struct latticeStruct * newLattice(int height, int width, int clear);	

void * printBasics(struct antStruct *, struct latticeStruct *);
void * displayGrid(struct latticeStruct * lattice);

void * direction(struct antStruct * ant, struct latticeStruct * lattice);
void * rv_Direction(struct antStruct * ant, struct latticeStruct * lattice);

void * paint(struct antStruct *, struct latticeStruct *);

void * move( struct antStruct *, struct latticeStruct *);
void * rvMove( struct antStruct *, struct latticeStruct *);

int successor( struct antStruct *, struct latticeStruct *, int );
int predecessor( struct antStruct *, struct latticeStruct *, int );

#endif
