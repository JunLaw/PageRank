#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>



typedef struct somm{
	int val;
	double cout;
	struct somm *pred;

}Sommet;


//Insertion d'un sommet predecesseur
void insert(Sommet *s1,Sommet *s2){
	if(s1->pred == NULL){
		s1->pred = s2;
	}else{
		Sommet *tmp = s1->pred;

		while(tmp->pred != NULL){
			tmp = tmp->pred;
		}
		tmp->pred = s2;
	}
}


//parcours des predecesseur du sommet s1
void parcours(Sommet *s1){
	printf("n°%d : \n",s1->val);
	Sommet *tmp = s1->pred;
	while(tmp != NULL){
		printf("%d , %f\n",tmp->val,tmp->cout);
		tmp = tmp->pred;
			
	}
	
}		
	
	
//lecture/verification du fichier passé en paramètre
void read_txt(){

}

//assignation des sommets predecesseurs au sommet
void assign_v(){

}

//multiplication du vecteur x (1/N) et la matrice web
void multiplication(Sommet * Matrice, int nb_sommet, double * Vecteur,double * Res)
{
		
	
	for(int i = 0 ; i < nb_sommet ; i++)
	{
		//printf("it %d\n",i);
		Sommet *tmp = Matrice[i].pred;	
		while(tmp != NULL)
		{

			//printf("1) Res[i] = %lf ",Res[i]);
			Res[i] += tmp->cout * Vecteur[tmp->val - 1];
			//printf("2) Res[i] = %lf\n",Res[i]);
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

//verification de convergence par comparaison du vecteur n-1 et n
int compare(double *x1,double *x2,int taille){
	for(int i = 0;i<taille;i++){
		if(fabs(x1[i]-x2[i]) >= 0.000001 ){
			return 1;
		}
	}
	return 0;
}


int main( void )
{

	 float temps;
    clock_t t1, t2;
 
    t1 = clock();
	/***
	INITIALISATION
	nbr_sommet = nombre de sommet (chaine de caractère)
	nbr_arcs = nombre d'arcs
	ctmp = chaine de caractère tampon pour lecture d'une ligne (une ligne est une representation d'un sommet et de ses voisins avec le poids des arcs)
	numsommet = numero du sommet à traiter
	nbrsucc = nombre de voisins du sommet traité
	num = recuperation du numero du voisins actuel du sommet traité
	sommet = nombre de sommets (entier)
	arcs = nombre d'arcs 
	prob = poids de l'arcs courant traité
	n = curseur temporaire sur la chaine de caractère traité
	vec = vecteur ligne d'initialisation à 1/(nombre de sommet)
	Res = vecteur ligne de resolution (resultat de xG ou xP)
	alpha = Page rank parameter
	j = iterateur de convergence
	***/

	 srand( time( NULL ) );
	int i;
	FILE *F;
	char nbrsommet[10000]="";
	char nbrarcs[10000]="";
	char *ctmp ;
	int numsommet,nbrsucc,num;
	int sommet;
	int arcs;
	double prob;
	int n;
	
 	double alpha = 0.85;
 	int j =0;

 	/***
		OUVERTURE/LECTURE FICHIER
		Etape 1:ouverture
		Etape 2 : lecture + conversion du nombre de sommets et d'arcs
 	***/

 	//Etape 1
 	if(!(F = fopen("web1.txt","r"))){
		printf("null");
		return 1;
	}

	//Etape 2
 	 fgets(nbrsommet,10000,F);
	 fgets(nbrarcs,10000,F);
	 sscanf(nbrsommet,"%d",&sommet);
	 sscanf(nbrarcs,"%d",&arcs);
	

	 /***
			INITIALISATION VECTEUR : 
			e = vecteur avec 1 partout
			vec = vecteur initial de x*P et x*G
			res_1 = vecteur de comparaison de convergence avec Res
			f_t = vecteur ligne stochastique 1 si pas de voisin 0 sinon

	 ***/
	
	double *e = malloc(sommet*sizeof(double));
	for(int i = 0;i<sommet;i++){e[i] = 1.0;}
	

		double *res_1 = malloc(sommet*
			sizeof(double));
	for(int i = 0;i<sommet;i++){res_1[i] = 0.0;}	

	double *f_t = malloc(sommet*sizeof(double));
	Sommet *tabSommet = (Sommet*) malloc (sommet * sizeof(Sommet));

	double *Res = (double*) malloc(sommet*sizeof(double));
	for(int i = 0;i<sommet;i++){Res[i] = 0.0;}
 	double *vec = malloc(sommet*sizeof(double));

 	for(int i = 0;i<sommet;i++){
		vec[i] = ((double) 1.0 / (double) sommet );
		printf("%lf",vec[i]);
	}
	

	/***
		Initialisation sommet et voisins
		Etape 1: creation de tout les sommets puis insertions dans un tableau les regroupant tous
		Etape 2: Recuperation de la ligne courante avec numero du sommet traité / nombre de voisins / numero du voisins courant / poids de l'arcs
		Etape 3: Lecture + Creation du sommets voisins (predecesseur) puis liaison (fct insert) avec le sommets courant
	***/
	
	//Etape 1
	


	 //Etape 2
	 for(int i = 0; i < sommet; i ++){
	 	ctmp = (char*) malloc (100000000 *sizeof(char));
	 	fgets(ctmp,100000000,F);
	 	int a = sscanf(ctmp,"%d %d %n",&numsommet,&nbrsucc,&n);
	 	printf("nums = %d,nbrsucc = %d\n",numsommet,nbrsucc);


	 	ctmp += n;

	 	/*** A garder si on traite avec successeur
	 	if(nbrsucc == 0){
	 		f_t[i] = 1;
	 	}else{
	 		f_t[i] = 0;
	 	}
	 	***/

	 	//Etape 3
	 	for(int j = 0; j < nbrsucc;j++){
	 	sscanf(ctmp," %d %lf %n",&num,&prob,&n);
	 			if( (num <= sommet) ) {
	 			//printf("num = %d,prob = %lf\n",num,prob);
	 			Sommet *atmp = (Sommet*) malloc(sizeof(Sommet));
	 			atmp->cout = prob;
	 			atmp->val = i+1;
	 			atmp->pred = NULL;
	 			insert(&tabSommet[num-1],atmp);
				


	 			
	 			}
	 			ctmp +=n;

	 		}
	 	

	 }

	  t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps = %f\n", temps);

	 /***
		INITIALISATION DU VECTEUR F_T

	 ***/
for(int i = 0;i<sommet;i++){
	if(tabSommet[i].pred == NULL){
		f_t[i] = 1;
	}else{
		f_t[i] = 0;
	}
}
	
//parcours(&tabSommet[0]);
	/***
		Test de convergence
		Etape 1 : initialisation du vecteur res n-1 
		Etape 2 : xG
		Etape 3 : verification de la convergence
		Etape 4 : Affichage du nombre d'iteration + vecteur convergent
	***/
	for(int j = 0; j<10;j++){
		//Etape 1
		for(int i = 0; i<sommet;i++){res_1[i] = Res[i];}
		//Etape 2
			
		
	multiplication_xG(tabSommet, sommet, vec, Res, alpha, f_t, e);
		j++;

	
}
		for(int i = 0 ; i < sommet ; i++) {printf("%lf ",Res[i]);}
		printf("\n");

		printf("nbr iteration = %d",j);

		
	
	free(Res);
	free(tabSommet);



  return 0;
}