#include <stdio.h>
#include <stdlib.h>

#include "arbres.h"
#include "analysis.h"

/* -------------------------------------------------------------------------- */

void save_tree_in_dot_file (t_abr arbre, t_abr father, FILE * file, 
			    int f_index, int *index) {
  if (arbre) {
    fprintf (file, "A%d [label=\"%d, %d\"];\n", *index, arbre->data.val, arbre->data.counter);
    if (father) {
      fprintf (file, "A%d -> A%d;\n", f_index, *index);
    } else { fprintf (file, "R -> A%d [color=white];\n", *index); }

    f_index = *index; /* l'arbre courant est le pere de fg et fd */
    (*index) ++;   
    save_tree_in_dot_file (arbre->fg, arbre, file, f_index, index);

    (*index) ++;
    save_tree_in_dot_file (arbre->fd, arbre, file, f_index, index);
  } else {    
    fprintf (file, "A%d_ [label=\"\",color=white];\n", *index);
    fprintf (file, "A%d -> A%d_ [color=white];\n", f_index, *index);
  }
} /* end of save_tree_in_dot_file_arbre */

/* -------------------------------------------------------------------------- */

void tree2dot (t_abr arbre) {
  FILE * file;
  int index = 1;

  file = fopen("tree.dot", "w");
  fprintf (file, "digraph G {\n");
  fprintf (file, "R [label=\"\",color=white];\n");

  save_tree_in_dot_file (arbre, NULL, file,0, &index);
  fprintf (file, "}\n");
  fclose (file);
  system ("dot -Tjpg -o tree.jpg tree.dot");
} /* end of tree2dot */

/* -------------------------------------------------------------------------- */

void save_tree_in_tex_file (t_abr arbre, t_abr father, FILE * file) {
  if (arbre) {
    if ((arbre -> fg) || (arbre -> fd)) {
      fprintf (file, "\\begin{bundle}{%d, %d}\n", arbre->data.val, arbre->data.counter);
      
      fprintf (file, "\\chunk{\n");
      save_tree_in_tex_file (arbre->fg, arbre, file);
      fprintf (file, "}\n");
      
      fprintf (file, "\\chunk{\n");
      save_tree_in_tex_file (arbre->fd, arbre, file);
      fprintf (file, "}\n");

      fprintf (file, "\\end{bundle}\n");
    } else { fprintf (file, "%d, %d\n", arbre->data.val, arbre->data.counter); }
  } 
} /* end of save_tree_in_tex_file_arbre */

/* -------------------------------------------------------------------------- */

void tree2tex (t_abr arbre) {
  FILE * file;

  file = fopen("tree.tex", "w");
  fprintf (file, "\\documentclass[landscape]{article}\n");
  fprintf (file, "\\usepackage[francais]{babel}\n");
  fprintf (file, "\\usepackage[latin1]{inputenc}\n");
  fprintf (file, "\\usepackage{epic}\n");
  fprintf (file, "\\usepackage{eepic}\n");
  fprintf (file, "\\usepackage{ecltree}\n");
  fprintf (file, "\\begin{document}\n");

  save_tree_in_tex_file (arbre, NULL, file);
  fprintf (file, "\\end{document}\n");
  fclose (file);
  system ("latex tree.tex; dvips -t a4 -t landscape tree -o tree.ps; convert tree.ps tree.jpg");
} /* end of tree2tex */

/* -------------------------------------------------------------------------- */

void free_tree (t_abr arbre) {
  if (arbre) {
    free_tree (arbre->fg);
    free_tree (arbre->fd);
    free (arbre);
  }  
} /* end of free_tree */

/* -------------------------------------------------------------------------- */

t_abr empty_tree (void) { return NULL; }

/* -------------------------------------------------------------------------- */

void prof_infixe (t_abr arbre) {
  if (arbre) {
    prof_infixe (arbre->fg);
    //printf ("%d ", arbre -> val);
    prof_infixe (arbre->fd);
  }
} /* end of prof_infixe */

/* -------------------------------------------------------------------------- */

void prof_droite (t_abr arbre) {
  if (arbre) {
    prof_droite (arbre->fd);
    //printf ("%d ", arbre -> val);
    prof_droite (arbre->fg);
  }
} /* end of prof_droite */

t_abr new_abr (struct countStruct data, t_abr fg , t_abr fd) {
  t_abr arbre;

  arbre = (t_abr) malloc (sizeof (t_noeud));
  if (arbre) {
    arbre -> data.val = data.val;
    arbre -> fg = fg;
    arbre -> fd = fd;
    arbre -> data.counter = 1;
  }
  return arbre;
} /* end of new_abr */

void ajout_feuille (t_abr * arbre, struct countStruct data) {
	if (*arbre) {	
		if (data.val < (*arbre) -> data.val){ 
	    		ajout_feuille (&((*arbre) -> fg), data);
    		}else if(data.val == (*arbre)->data.val){
			(*arbre)->data.counter += data.counter;			//Remettre data.counter
		}else ajout_feuille (&((*arbre) -> fd), data);
	} else {
		printf("vreatinf new abr\n");
    		*arbre = new_abr (data, NULL, NULL);
  	}
} /* end of ajout_feuille */

t_abr merge_tree(t_abr tree1, t_abr * tree2){		//merges tree1 in tree2
							//After calling this function, tree1 still exists, remember to free() it if necessary
		
	if(tree1){
		merge_tree(tree1->fg, tree2);
		ajout_feuille(tree2, tree1->data);
		printf("tree 1 : val : %d\t counter : %d\n", tree1->data.val, tree1->data.counter);
		merge_tree(tree1->fd, tree2);


	}


}
int  sumCounter(t_abr arbre, int  count){
	if(arbre){
		sumCounter( arbre->fg, count);
		(count) += arbre->data.counter;
		sumCounter( arbre->fd, count);
	}
	return count;
}
