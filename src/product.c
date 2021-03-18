#include "product.h"

//multiplication du vecteur x (1/N) et la matrice web
void multiplication(Sommet *Matrice, int nb_sommet, double * Vecteur,double * Res)
{
		
	
	for(int i = 0 ; i < nb_sommet ; i++)
	{
		Sommet *tmp = Matrice[i].pred;	
		while(tmp != NULL)
		{
			
			Res[i] += tmp->cout * Vecteur[tmp->val - 1];
			
			tmp = tmp->pred;
		}
		
		

	}
	
}
//multiplication d'un vecteur colonne par vecteur ligne renvoie un double resultat
double mult_scalaire(double* Vect_l, double* Vect_c, int taille){
	double res;
	
	for(int i=0; i<taille; i++){
		res += Vect_l[i]*Vect_c[i];
	}
	
	return res;
}

//multiplication vecteur par un scalaire
void mult_alpha_vecteur_ligne(double alpha, double * Vecteur, int taille){
	
	for(int i=0; i<taille; i++){
		Vecteur[i] *= alpha;
	}
	
}

//somme de deux vecteur ligne
void somme_vecteur_ligne(double* vect1, double* vect2, int taille, double* res){
	
	for(int i=0; i<taille; i++){
		res[i] = vect1[i]+vect2[i];
	}
	
}

// xG = alpha * x * P + [(1-alpha)(1/N) + alpha * (1/N)(x * f^t)]e
void multiplication_xG(Sommet * Matrice, int nb_sommet, double * Vecteur,double * Res, double alpha,double* f_t,double* e){
	double scalaire;
	multiplication(Matrice,nb_sommet,Vecteur,Res);
	mult_alpha_vecteur_ligne(alpha,Res,nb_sommet);
	scalaire = mult_scalaire(Vecteur,f_t,nb_sommet);
	scalaire *= alpha*(1.0/(double) nb_sommet); 
	scalaire += (1.0-alpha)*(1.0/(double) nb_sommet);
	mult_alpha_vecteur_ligne(scalaire,e,nb_sommet);
	somme_vecteur_ligne(Res,e,nb_sommet,Res);
	//maj de e, au cas où on devrait le réutiliser
	for(int i=0; i<nb_sommet;i++){e[i]=1.0;}
}