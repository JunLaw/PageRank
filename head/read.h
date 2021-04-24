#ifndef __READ_H
#define __READ_H

#include "pagerank.h"

int check_url(const char *str_check);
//assignation des sommets predecesseurs au sommet
int read_txt(double *f_t,Sommet *tabSommet,int sommet,FILE *F,int *liste);

void read_txt_(Sommet *tabSommet,int sommet,FILE *F,int *k);


//verification de convergence par comparaison du vecteur n-1 et n
int compare(double *x1,double *x2,int taille,double precision);


#endif