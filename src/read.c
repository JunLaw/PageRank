#include "read.h"

int check_url(const char *str_check){
	int err;
			regex_t preg;
			const char *str_regex = "[-_[:alnum:]]+\.txt";
			err = regcomp (&preg, str_regex, REG_NOSUB | REG_EXTENDED);

			if(err == 0)
			{

			 	int match = regexec(&preg,str_check,0,NULL,0);
			 	regfree(&preg);

			 	if(match == 0)
			 	{
			 		return 0;
			 	}
			 	else
			 	{
			 		return 1;
			 	}
			 }
			else{
			
			return 1;
		}
		return 0;

}

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

//assignation des sommets predecesseurs au sommet
void read_txt_(Sommet *tabSommet,int sommet,FILE *F,int *k)
{
	int n;
	int dangling_node = 0;
	int numsommet,nbrsucc,num;		
	

	double prob;
	
	 for(int i = 0; i< sommet; i++){
	 	Sommet *tmp = malloc(sizeof(Sommet));
	 	tmp->val = i+1;
	 	tmp->pred = NULL;
	 	tmp->cout = 0.0;
	 	tabSommet[i] = *tmp;

	 }

	 for(int i = 0; i < sommet; i ++)
	 {

		char *ctmp = malloc (630000* sizeof(char));
		char *memCtmp = ctmp;
	 	fgets(ctmp,630000,F);
		
	 	sscanf(ctmp,"%d %d %n",&numsommet,&nbrsucc,&n);
	 	//printf("num = %d, nbrsucc = %d\n",numsommet,nbrsucc);
	 	ctmp += n;

	 	
	 	if(nbrsucc == 0)
	 	{
	 		*k = *k - 1;
	 		dangling_node++;
	 		Sommet tmp = tabSommet[numsommet-1];
	 		tabSommet[numsommet-1] = tabSommet[*k];
	 		tabSommet[*k] = tmp;
	 		free(memCtmp);
	 		continue;
	 	}

	 	//Etape 3
	 	for(int j = 0; j < nbrsucc;j++)
	 	{
	 		sscanf(ctmp," %d %lf %n",&num,&prob,&n);
	 		//printf("%d, %lf ",num,prob);
	 			if( (num <= sommet) )
	 			{
	 				Sommet *atmp = malloc(sizeof(Sommet));
	 				atmp->cout = prob;
	 				atmp->val = i+1;
	 				atmp->pred = NULL;
	 				int zed = 0;
	 				int cpt = 0;
	 				//printf("num = %d\n",num);
	 				while( (zed == 0) || (cpt <= sommet)){
	 					if(tabSommet[cpt].val == num){
	 						//printf("%d\n",cpt);
	 						zed = 1;
	 						break;
	 					}
	 					cpt++;
	 				}
	 				insert(&tabSommet[cpt],atmp);
	 				
	 			}
	 				ctmp += n;
	 	}
	 	free(memCtmp);
	 	//printf("\n");
	 }
	/*
	 printf("number of dangling node = %d\n",dangling_node);
	 printf("number of non dangling node = %d\n",*k);
	 for(int i = 0;i<sommet;i++){
	 	printf("%d ----->  ",tabSommet[i].val);
	 	Sommet *tmp = (&tabSommet[i])->pred;
	 	while(tmp != NULL){
	 		printf("%d -> %lf ",tmp->val,tmp->cout);
	 		tmp = tmp->pred;
	 	}
	 	printf("\n");
	 }
	 */

}


int read_txt(double *f_t,Sommet *tabSommet,int sommet,FILE *F,int *liste)
{
	int n;
	int cpt = 0;
	int j = 0;
	int numsommet,nbrsucc,num;
	double prob;
	 for(int i = 0; i< sommet; i++){
	 	Sommet *tmp = malloc(sizeof(Sommet));
	 	tmp->val = i+1;
	 	tmp->pred = NULL;
	 	tabSommet[i] = *tmp;

	 }

	 for(int i = 0; i < sommet; i ++)
	 {
	 	
		char *ctmp = malloc (1300000* sizeof(char));
		char *memCtmp = ctmp;
	 	fgets(ctmp,1300000,F);
	 	sscanf(ctmp,"%d %d %n",&numsommet,&nbrsucc,&n);
	 	//printf("num = %d, nbrsucc = %d\n",numsommet,nbrsucc);
	 	ctmp += n;
	 	if(nbrsucc == 0)
	 	{
	 		f_t[i] = 1.0;
	 		cpt++;
	 		liste[j] = numsommet;
	 		j++;
	 		free(memCtmp);
	 		continue;
	 	}else
	 	{
	 		f_t[i] = 0.0;
	 	}
	 	

	 	//Etape 3
	 	for(int j = 0; j < nbrsucc;j++)
	 	{
	 		sscanf(ctmp," %d %lf %n",&num,&prob,&n);

	 			if( (num <= sommet) )
	 			{
	 				Sommet *atmp = malloc(sizeof(Sommet));
	 				atmp->cout = prob;
	 				atmp->val = i+1;
	 				atmp->pred = NULL;
	 				insert(&tabSommet[num-1],atmp);
	 				
	 			}
	 				ctmp += n;
	 	}
	 	free(memCtmp);
	 	
	 }

	 /*
	 for(int i = 0;i<sommet;i++){
	 	printf("%d ----->  ",tabSommet[i].val);
	 	Sommet *tmp = (&tabSommet[i])->pred;
	 	while(tmp != NULL){
	 		printf("%d -> %lf ",tmp->val,tmp->cout);
	 		tmp = tmp->pred;
	 	}
	 	printf("\n");
	 }
	 */
	 liste[cpt] = -1; 
	 return cpt;
}



void max(FILE *F,int nbrsommet){
	int max = 0;
	int n = 0;
	int numsommet,nbrsucc;

		for(int i = 0; i< nbrsommet;i++){
		char *ctmp = malloc (300000* sizeof(char));
		char *memCtmp = ctmp;
	 	fgets(ctmp,300000,F);

	 	sscanf(ctmp,"%d %d %n",&numsommet,&nbrsucc,&n);
	 	ctmp += n;
	 	if(max < nbrsucc){
	 		max = nbrsucc;
	 	}

	 	free(memCtmp);
	 }

	printf("max neighbour = %d",max);
}


//verification de convergence par comparaison du vecteur n-1 et n
int compare(double *x1,double *x2,int taille,double precision){
	for(int i = 0;i<taille;i++){
		if(fabs(x1[i]-x2[i]) >= precision ){
			return 1;
		}
	}
	return 0;
}


