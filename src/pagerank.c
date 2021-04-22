#include "pagerank.h"
#include "read.h"
#include "product.h"
	
	int main(int argc,char **argv){
	srand( time( NULL ) );
	FILE *F;
	char nbrsommet[10000]="";
	char nbrarcs[10000]="";	
    clock_t t1, t2,t3;
    t1 = clock();
	int sommet;
	int arcs;
 	double alpha = 0.0;
 	double precision = 0.0;
 	int j = 0;
	char *str = "./graph/";
 		
 	if (argc == 4 && !check_url(argv[1])){
 		char *str_g = malloc(sizeof(char) * strlen(str) + strlen(argv[1]));
 		strcpy(str_g,str);
 		strcat(str_g,argv[1]);
 		if(!(F = fopen(str_g,"r"))){return 1;}
 		sscanf(argv[2],"%lf",&precision);
 		sscanf(argv[3],"%lf",&alpha);
 		free(str_g);
 	}else{
 		return 1;
 	}

	 fgets(nbrsommet,10000,F);
	 fgets(nbrarcs,10000,F);
	 sscanf(nbrsommet,"%d",&sommet);
	 sscanf(nbrarcs,"%d",&arcs);
 	
	double *e = malloc(sommet*sizeof(double));
	for(int i = 0;i<sommet;i++){e[i] = 1.0;}
	
	double *res_1 = malloc(sommet*sizeof(double));
	for(int i = 0;i<sommet;i++){res_1[i] = 0.0;}	

	double *f_t = malloc(sommet*sizeof(double));

	Sommet *tabSommet = NULL;
	tabSommet = malloc (sommet * sizeof(Sommet));

	double *Res = (double*) malloc(sommet*sizeof(double));
	for(int i = 0;i<sommet;i++){Res[i] = 0.0;}
 	double *vec = malloc(sommet*sizeof(double));

 	//double *w = malloc(sommet*sizeof(double));
	Sommet *H12 = NULL;
 	

 	int tmp = sommet;
 	int *k = &tmp;
 	for(int i = 0;i<sommet;i++){vec[i] = ((double) 1.0 / (double) sommet );}
	read_txt_(tabSommet,sommet,F,k);
	//read_txt(f_t,tabSommet,sommet,F);
	double *theta = malloc((*k)*sizeof(double));
	Vector *w1 = malloc((*k)*sizeof(Vector));
	Vector *v1 = malloc((*k)*sizeof(Vector));
	for(int i = 0;i<(*k);i++){
		w1[i].cout = (double) (1.0 / (double) (sommet) );
		w1[i].val = tabSommet[i].val;
		v1[i].cout = (double) (1.0 / (double) (sommet) );
		v1[i].val = tabSommet[i].val;
	}
	Vector *w2 = malloc((sommet-(*k))*sizeof(Vector));
	Vector *v2 = malloc((sommet-(*k))*sizeof(Vector));
	if(sommet != (*k)){
	
	for(int i = (*k);i<sommet;i++){
		w2[i].cout = (double) (1.0 / (double) (sommet) );
		w2[i].val = tabSommet[i].val;
		v2[i].cout = (double) (1.0 / (double) (sommet) );
		v2[i].val = tabSommet[i].val;
	}
	}

	for(int i = 0;i<(*k);i++){
		theta[i] = (double) (1.0 / (double) ((*k)+1) );
	}

	Sommet *H11 = NULL;
	H11 = malloc((*k)*sizeof(Sommet));
	for(int i = 0;i<(*k);i++){
		H11[i] = tabSommet[i];
	}
	 for(int i = 0;i<(*k);i++){
	 	//printf("%d ----->  ",H11[i].val);
	 	Sommet *tmp = (&H11[i])->pred;
	 	while(tmp != NULL){
	 		//printf("%d -> %lf ",tmp->val,tmp->cout);
	 		tmp = tmp->pred;
	 	}
	 	//printf("\n");
	 }
	 
	if(sommet != (*k)){
	H12 = malloc((sommet-(*k))*sizeof(Sommet));
	for(int i = (*k);i<sommet;i++){
		H12[i-((*k))] = tabSommet[i];
	}
	
	 for(int i = 0;i<(sommet-(*k));i++){
	 	//printf("%d ----->  ",H12[i].val);
	 	Sommet *tmp = (&H12[i])->pred;
	 	while(tmp != NULL){
	 		//printf("%d -> %lf ",tmp->val,tmp->cout);
	 		tmp = tmp->pred;
	 	}
	 	//printf("\n");
	 }
	}
	double theta_k_1_tmp = (double) (1.0 / (double) ((*k)+1) );
	double *theta_k_1 = &theta_k_1_tmp;
	Vector *res_w1 = malloc((*k)*sizeof(Vector));
	Vector *res_v1 = malloc((*k)*sizeof(Vector));
	multiplication_dangling_version(w1,w2,v1,v2,theta,alpha,sommet,(*k),H11,H12,e,res_w1,res_v1,theta_k_1);
	
    //read_txt(f_t,tabSommet,sommet,F);
	t3 = clock();
	printf("Read time : %ld\n",(t3-t1)/CLOCKS_PER_SEC);
	/*
	do
	{
		//Etape 1
		for(int i = 0; i<sommet;i++){res_1[i] = Res[i];
			Res[i] = 0.0;
		}
		//Etape 2
		multiplication_xG(tabSommet, sommet, vec, Res, alpha, f_t, e);
		for(int i = 0;i<sommet;i++){vec[i] = Res[i];}
		j++;
	}while(compare(res_1,Res,sommet,precision));
	
	
	FILE *fic = fopen("vec.txt","w+");		
	for(int i = 0 ; i < sommet ; i++) {fprintf(fic," %lf ",Res[i]);}
	printf("nbr iteration = %d\n",j);	
	t2 = clock();
	printf("PageRank time : %ld\n",(t2-t3)/CLOCKS_PER_SEC);
	*/

	free(Res);
	free(e);
	free(vec);
	free(res_1);
	free(f_t);
	free(tabSommet);
	fclose(F);
	//fclose(fic);
  return 0;
}