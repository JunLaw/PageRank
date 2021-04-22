#include "product.h"

//multiplication du vecteur x (1/N) et la matrice web
void multiplication(Sommet *Matrice, int nb_sommet, double * Vecteur,double * Res)
{
		
	
	for(int i = 0 ; i < nb_sommet ; i++)
	{
		Sommet *tmp = Matrice[i].pred;

		while(tmp != NULL)
		{
			//printf("%d\n",tmp->val);
			//printf("%lf * %lf\n",tmp->cout,Vecteur[tmp->val - 1]);
			Res[i] += tmp->cout * Vecteur[tmp->val - 1];
			
			tmp = tmp->pred;
		}
		//printf("RES[%d] = %lf\n",i,Res[i]);
		

	}
	
}
//multiplication d'un vecteur colonne par vecteur ligne renvoie un double resultat
double mult_scalaire(double* Vect_l, double* Vect_c, int taille){
	double res=0.0;
	
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

void mult_alpha_vecteur_ligne_vector(double alpha,Vector *Vecteur,int taille,Vector *res){
	for(int i = 0; i<taille;i++){
		res[i].cout = alpha * Vecteur[i].cout;
	}
}

void somme_vecteur_ligne_vector(double *vect1,Vector *vect2,int taille,double *res){
	for(int i = 0;i<taille;i++){
		res[i] = vect1[i] + vect2[i].val;
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


void multiplication_dangling_version(Vector *w1,Vector *w2,Vector *v1,Vector *v2,double *theta,double alpha,int n,int k,Sommet *H11,Sommet *H12,double *e,Vector *res_w1,Vector *res_v1,double *theta_k_1){
	double *res_1 = malloc(k*sizeof(double));
	double *res = malloc(k*sizeof(double));
	do{
		for(int i = 0; i<k;i++){
			res_1[i] = res[i];
			res[i] = 0.0;
		}
	
	multiplication(H11,k,theta,res);
	mult_alpha_vecteur_ligne(alpha,res,k);
	mult_alpha_vecteur_ligne_vector((1.0-alpha),v1,k,res_v1);
	mult_alpha_vecteur_ligne_vector((alpha*(*theta_k_1)),w1,k,res_w1);
	somme_vecteur_ligne_vector(res,res_v1,k,res);
	somme_vecteur_ligne_vector(res,res_w1,k,res);
	*theta_k_1 = 1 - mult_scalaire(res,e,k);
	for(int i=0; i<n;i++){e[i]=1.0;}
	for(int i = 0;i<k;i++){
		res_w1[i].cout = 0.0;
		res_v1[i].cout = 0.0;

	}

	
	for(int i = 0; i< k;i++){
		printf("theta[%d] = %lf\n",i,theta[i]);
	}
	printf("theta_k_1 = %lf",*theta_k_1);

	for(int i = 0;i<k;i++){theta[i] = res[i];}
	}while(compare(res_1,res,k,0.00001));

	

}
