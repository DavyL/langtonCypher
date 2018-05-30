#ifndef STRUCT_H
#define STRUCT_H

//Not really clean to have these structures in a separate headers but it works
//Will be fixed when I get my hands on K&R

struct countStruct{
	
	int val;
	int counter;
	
};

typedef struct _t_noeud {
  struct countStruct data;
  struct _t_noeud *fg, *fd; 
} t_noeud;

typedef t_noeud * t_abr;

struct packetStruct{

	t_abr tree;

	struct antStruct * ant;

	int height;
	int width;

	int blockSize;

	int listSize;

	int * binary;
};

#endif
