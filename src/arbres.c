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

void tree2dot (t_abr arbre, int height, int width) {
  FILE * file;
  int index = 1;
  char filename[sizeof "pdf/tree10x10.dot"];
  sprintf(filename, "pdf/file%02dx%02d.dot", height, width);
  file 	= fopen(filename, "w");

  fprintf (file, "digraph G {\n");
  fprintf (file, "R [label=\"\",color=white];\n");

  save_tree_in_dot_file (arbre, NULL, file,0, &index);
  fprintf (file, "}\n");
  fclose (file);

   char command[sizeof "dot -Tjpg -o pdf/tree10x10.jpg pdf/tree10x10.dot"];
   sprintf(command, "dot -Tjpg -o pdf/tree%02dx%02d.jpg pdf/tree%02dx%02d.dot", height, width, height, width);

  system (command);
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

void tree2tex (t_abr arbre, int height, int width) {
  FILE * file;
  char filename[sizeof "pdf/tree10x10.tex"];
  sprintf(filename, "pdf/tree%02dx%02d.tex", height, width);
  file 	= fopen(filename, "w");
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
  char command[sizeof "latex pdf/tree10x10.tex; dvips -t a4 -t landscape tree -o pdf/tree10x10.ps; convert pdf/tree10x10 pdf/tree10x10.jpg"];
  sprintf(command, "latex pdf/tree%02dx%02d.tex; dvips -t a4 -t landscape tree -o pdf/tree%02dx%02d.ps; convert pdf/tree%02dx%02d.ps pdf/tree%02dx%02d.jpg", height, width, height, width, height, width, height, width);

  system (command);
//ystem ("latex tree.tex; dvips -t a4 -t landscape tree -o tree.ps; convert tree.ps tree.jpg");
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
    arbre -> data.counter = data.counter;
    printf("Successfully created a new tree\n");
    return arbre;
  }else
	  return NULL;
} /* end of new_abr */

void ajout_feuille (t_abr * arbre, struct countStruct data1) {
	
	if (*arbre) {

		if (data1.val < ((*arbre)->data).val){	
	    		ajout_feuille (&((*arbre) -> fg), data1);
    		}else if(data1.val == (*arbre)->data.val){
			(*arbre)->data.counter += data1.counter;	
		}else ajout_feuille (&((*arbre) -> fd), data1);
	} else {
    		*arbre = new_abr (data1, NULL, NULL);
  	}
} /* end of ajout_feuille */

t_abr * merge_tree(t_abr * tree1, t_abr * tree2){		//merges tree1 in tree2
							//After calling this function, tree1 still exists, remember to free() it if necessary
	
/*	if(!tree2){
		//tree2 = tree1;
		tree2 = new_abr(	
	}
*/
	if(*tree1){
		if(*tree2){
			ajout_feuille(tree2, (*tree1)->data);
		}else{
			tree2 = malloc(sizeof(t_abr));
			*tree2 = new_abr((*tree1)->data, NULL, NULL);
		}
		printf("Ajout d'une feuille a tree2 avec val : %d\tcounter:%d\n",(*tree1)->data.val, (*tree1)->data.counter);
		merge_tree(&((*tree1)->fg), tree2);
		
		merge_tree(&((*tree1)->fd), tree2);
	}
	return tree2;

}

int  sumCounter(t_abr arbre, int * count){		//Sums the order of every equiv class
							//If used on a tree that contains every n*m grids it should be equal to 2^(n*m)
	if(arbre){
		sumCounter( arbre->fg, count);
		(*count) += arbre->data.counter;
		sumCounter( arbre->fd, count);
	}
	return *count;
}

int  sumProductCounter(t_abr arbre, int * count){
	if(arbre){
		sumCounter( arbre->fg, count);
		(*count) += arbre->data.counter * arbre->data.val;
		sumCounter( arbre->fd, count);
	}
	return *count;
}

int elemCounter(t_abr arbre, int * c){
	if(arbre){
		*c += 1;
		sumCounter( arbre->fg, c);
		sumCounter( arbre->fd, c);
	}
	return *c;
}

void getTreeInfo(t_abr arbre, int * count, int * numEquivClass, int * numEquivClassMult ){

	if(arbre){
		(*count) 		+= arbre->data.counter;
		(*numEquivClass)	+= 1;
		(*numEquivClassMult)	+= (arbre->data.val);
		
		printf("SLT\n");

		getTreeInfo( arbre->fg, count, numEquivClass, numEquivClassMult);
		getTreeInfo( arbre->fd, count, numEquivClass, numEquivClassMult);
	}
}


