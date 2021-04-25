#include "product.h"
#include "read.h"

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

void mult_dangling(Sommet *Matrice,int nb_sommet,Vector *Vecteur,double *Res,int *liste,int on ){
	
	int j = 0;
	int x = 0;
	if(on ==1){
	for(int i = 0;i<nb_sommet;i++){
		Sommet *tmp = Matrice[i].pred;
		if(i == liste[x]-1){
			x++;
			continue;
		}
		while(tmp !=NULL){
			Res[i] += tmp->cout * Vecteur[tmp->val-1].cout;
			j++;
			tmp = tmp->pred;			
		}
		j=0;
		free(tmp);
		
	}
}else{
	for(int i = 0;i<nb_sommet;i++){
		Sommet *tmp = Matrice[i].pred;
		if(i == liste[x]-1){
			while(tmp != NULL){
			Res[i] += tmp->cout * Vecteur[tmp->val-1].cout;
			tmp = tmp->pred;
		}	
			x++;
			free(tmp);
			
		}else{
			continue;
		}
	}
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

void mult_alpha_vecteur_ligne_after(double alpha,double *final,int n,int *liste){
	int x = 0;
	for(int i = 0; i< n;i++){
		if(liste[x]-1 == i){
			final[i] *= alpha;
			x++; 
		}else{
			continue;
		}
	}
}


void multiplication_sparse_matrix(double alpha,Vector *vecteur,int taille,Vector *res,int *liste,int on){
	int x = 0;
	if(on == 1){//non-dangling
		
		for(int i = 0;i<taille;i++){
			if(liste[x] == vecteur[i].val){
				
				res[i].cout = 0.0;
				x++;
				continue;
			}else{
			
				res[i].cout = alpha * vecteur[i].cout;
			}
		}

	}else{//dangling
		for(int i = 0;i<taille;i++){
			if(liste[x] == vecteur[i].val){
				res[i].cout = alpha * vecteur[i].cout;
				x++;
			}else{
				res[i].cout = 0.0;
				continue;
			}
		}
	}
}

void addition_sparse_matrix(double *vect1,Vector *vect2,int taille,double *res){

}

void somme_vecteur_ligne_vector(double *vect1,Vector *vect2,int taille,double *res){
	for(int i = 0;i<taille;i++){
		res[i] = vect1[i] + vect2[i].cout;
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
	for(int i=0; i<nb_sommet;i++){e[i]=1.0;}
}


double* multiplication_dangling_version(Vector *w1,Vector *w2,Vector *v1,Vector *v2,Vector *theta,double alpha,int n,int k,Sommet *H11,Sommet *H12,double *e,Vector *res_w1,Vector *res_v1,double *theta_k_1,double precision,int *liste, int *q){
	double *res_1 = malloc(n*sizeof(double));
	double *res = malloc(n*sizeof(double));
	int j = 0;
	do{
		for(int i = 0; i<n;i++){
			res_1[i] = res[i];
			res[i] = 0.0;
		}
	
			
		mult_dangling(H11,n,theta,res,liste,1);
	
		mult_alpha_vecteur_ligne(alpha,res,n);

		multiplication_sparse_matrix((alpha*(*theta_k_1)),w1,n,res_w1,liste,1);
	
		multiplication_sparse_matrix((1-alpha),v1,n,res_v1,liste,1);
	
		somme_vecteur_ligne_vector(res,res_v1,n,res);

		somme_vecteur_ligne_vector(res,res_w1,n,res);

		*theta_k_1 = 1 - mult_scalaire(res,e,n);

		for(int i=0; i<n;i++){e[i]=1.0;}

		for(int i = 0;i<n;i++) { res_w1[i].cout = 0.0;}
	
		for(int i = 0;i<n;i++){theta[i].cout = res[i];}
		
		(*q)++;
	
	} while(compare(res_1,res,k,precision));

	double *final = malloc(n*sizeof(double));

	for(int i = 0;i<n;i++) {final[i] = theta[i].cout;}
	
	mult_dangling(H12,n,theta,final,liste,0);

	mult_alpha_vecteur_ligne_after(alpha,final,n,liste);
	
	for(int i = 0;i<n;i++){res_v1[i].cout = 0.0;}
	for(int i = 0;i<n;i++){res_w1[i].cout = 0.0;}
		
	multiplication_sparse_matrix((1.0-alpha),v2,n,res_v1,liste,0);
	multiplication_sparse_matrix((alpha*(*theta_k_1)),w2,n,res_w1,liste,0);
	
	somme_vecteur_ligne_vector(final,res_w1,n,final);
	somme_vecteur_ligne_vector(final,res_v1,n,final);

	
	printf("nombre itération = %d\n",*q);
	//q = &j;
	return final;
	
}
