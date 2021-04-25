#ifndef __PRODUCT_H
#define __PRODUCT_H

#include "pagerank.h"

//multiplication du vecteur x (1/N) et la matrice web
void multiplication(Sommet *Matrice, int nb_sommet, double * Vecteur,double * Res);

//multiplication d'un vecteur colonne par vecteur ligne renvoie un double resultat
double mult_scalaire(double* Vect_l, double* Vect_c, int taille);

//multiplication vecteur par un scalaire
void mult_alpha_vecteur_ligne(double alpha, double * Vecteur, int taille);

//somme de deux vecteur ligne
void somme_vecteur_ligne(double* vect1, double* vect2, int taille, double* res);

// xG = alpha * x * P + [(1-alpha)(1/N) + alpha * (1/N)(x * f^t)]e
void multiplication_xG(Sommet * Matrice, int nb_sommet, double * Vecteur,double * Res, double alpha,double* f_t,double* e);

double* multiplication_dangling_version(Vector *w1,Vector *w2,Vector *v1,Vector *v2,Vector *theta,double alpha,int n,int k,Sommet *H11,Sommet *H12,double *e,Vector *res_w1,Vector *res_v1,double *theta_k_1,double precision,int *liste, int *q);


void mult_dangling(Sommet *Matrice,int nb_sommet,Vector *Vecteur,double *Res,int *liste,int on);



#endif