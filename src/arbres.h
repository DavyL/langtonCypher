#ifndef __ARBRES_H__
#define __ARBRES_H__

typedef struct _t_noeud {
  int val;
  int counter;
  struct _t_noeud *fg, *fd;
} t_noeud;

typedef t_noeud * t_abr;

void tree2dot (t_abr);
void tree2tex (t_abr);

void prof_droite (t_abr );
void prof_infixe (t_abr );
t_abr empty_tree (void);
void free_tree (t_abr );

void ajout_feuille (t_abr *, int);

t_abr new_abr (int, t_abr, t_abr);

#endif
