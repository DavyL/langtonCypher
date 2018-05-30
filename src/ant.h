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

struct latticeStruct * newLattice(int, int , int );	

int randColor(void  );

void * printBasics(struct antStruct *, struct latticeStruct *);
void * displayGrid(struct latticeStruct * );

void * direction(struct antStruct * , struct latticeStruct * );
void * rv_Direction(struct antStruct * , struct latticeStruct * );

void * paint(struct antStruct *, struct latticeStruct *);

void * move( struct antStruct *, struct latticeStruct *);
void * rvMove( struct antStruct *, struct latticeStruct *);

int successor( struct antStruct *, struct latticeStruct *, int );
int predecessor( struct antStruct *, struct latticeStruct *, int );

int freeLattice( struct latticeStruct *);

#endif
