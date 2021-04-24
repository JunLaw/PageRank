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
 		//printf("ok");
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
 	//printf("ok");
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
 	//printf("ok");
 	
	Sommet *H12 = NULL;
 	int *liste = malloc(sommet*sizeof(int));

 	int tmp = sommet;
 	int *k = &tmp;
 	for(int i = 0;i<sommet;i++){vec[i] = ((double) 1.0 / (double) sommet );}
 		int cpt = read_txt(f_t,tabSommet,sommet,F,liste);
 	
	t3 = clock();
	printf("Read time : %ld\n",(t3-t1)/CLOCKS_PER_SEC);

	Vector *theta = malloc((sommet-cpt)*sizeof(Vector));
	Vector *w1 = malloc((sommet-cpt)*sizeof(Vector));
	Vector *v1 = malloc((sommet-cpt)*sizeof(Vector));
	for(int i = 0;i<(sommet-cpt);i++){
		w1[i].cout = (double) (1.0 / (double) (sommet) );
		w1[i].val = tabSommet[i].val;
		v1[i].cout = (double) (1.0 / (double) (sommet) );
		v1[i].val = tabSommet[i].val;
	}
	
	Vector *w2 = malloc(cpt*sizeof(Vector));
	Vector *v2 = malloc(cpt*sizeof(Vector));
	
	
	for(int i = 0;i<cpt;i++){

		w2[i].cout = (double) (1.0 / (double) (sommet) );
		w2[i].val = tabSommet[i].val;
		v2[i].cout = (double) (1.0 / (double) (sommet) );
		v2[i].val = tabSommet[i].val;
	}

	
	

	Sommet *H11 = NULL;
	H11 = malloc((sommet-cpt)*sizeof(Sommet));
	H12 = malloc(cpt*sizeof(Sommet));
	int cptH12 = 0;
	int cptH11 = 0;
	int cc = 0;
	for(int i = 0;i<sommet;i++){
		if(liste[cc] == tabSommet[i].val){
			H12[cptH12] = tabSommet[i];
			cc++;
			cptH12++;
			//va dans H12
		}else{
			H11[cptH11] = tabSommet[i];
			theta[cptH11].val = tabSommet[i].val;
			theta[cptH11].cout = (double) (1.0 / (double) (sommet-cpt+1) );
			cptH11++;
			//va dans H11
		}
	
	}
	
	
	double theta_k_1_tmp = (double) (1.0 / (double) ((*k)+1) );
	double *theta_k_1 = &theta_k_1_tmp;
	Vector *res_w1 = malloc((sommet-cpt)*sizeof(Vector));
	Vector *res_v1 = malloc((sommet-cpt)*sizeof(Vector));
	double *last = malloc(sommet*sizeof(double));
	last = multiplication_dangling_version(w1,w2,v1,v2,theta,alpha,sommet,sommet-cpt,H11,H12,e,res_w1,res_v1,theta_k_1,precision,liste);
	/*
	for(int i = 0;i<sommet;i++){
		printf("last[%d] = %f\n",i,last[i]);
	}*/
	
	printf("Pagerank time : %ld\n",(t3-t1)/CLOCKS_PER_SEC);
	
	/*
	// Normal Pagerank
	do
	{
		//Etape 1
		for(int i = 0; i<sommet;i++){res_1[i] = Res[i];
			Res[i] = 0.0;
		}
		//Etape 2
		multiplication_xG(tabSommet, sommet, vec, Res, alpha, f_t, e);
		 for(int i = 0;i<sommet;i++){
		printf("res[%d] = %f\n",i,Res[i]);
		}
		//printf("\n");
		for(int i = 0;i<sommet;i++){vec[i] = Res[i];}
		j++;
	}while(compare(res_1,Res,sommet,precision));
	*/
	
	FILE *fic = fopen("vec.txt","w+");		
	for(int i = 0 ; i < sommet ; i++) {fprintf(fic," %f ",last[i]);}
	printf("nbr iteration = %d\n",j);	
	t2 = clock();
	printf("PageRank time : %ld\n",(t2-t3)/CLOCKS_PER_SEC);
	

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