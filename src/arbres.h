#ifndef __ARBRES_H__
#define __ARBRES_H__

#include "struct.h"
#include "analysis.h"

void tree2dot (t_abr, int, int);
void tree2tex (t_abr, int, int);

void prof_droite (t_abr );
void prof_infixe (t_abr );
t_abr empty_tree (void);
void free_tree (t_abr );

void ajout_feuille (t_abr *, struct countStruct);

t_abr new_abr (struct countStruct, t_abr, t_abr);

t_abr * merge_tree(t_abr *, t_abr * );


//For the functions below see .c 
int sumCounter(t_abr , int *);
int elemCounter(t_abr , int *);
int sumProductCounter(t_abr , int *);
void getTreeInfo(t_abr, int *, int *, int *);
#endif
