#include "pagerank.h"
#include "read.h"
#include "product.h"
	
	int main(int argc,char **argv){
	srand( time( NULL ) );
	int i;
	FILE *F;
	char nbrsommet[10000]="";
	char nbrarcs[10000]="";
	float temps;
    clock_t t1, t2;
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

 	for(int i = 0;i<sommet;i++){vec[i] = ((double) 1.0 / (double) sommet );}
 		printf("%lf\n",vec[0]);
	int *liste_succ = malloc(sommet*sizeof(int));

	read_txt(f_t,tabSommet,sommet,F,liste_succ);
	
	do
	{
		//Etape 1
		for(int i = 0; i<sommet;i++){res_1[i] = Res[i];
			Res[i] = 0.0;
		}
		//Etape 2
			//multiplication(tabSommet,sommet,vec,Res);
		multiplication_xG(tabSommet, sommet, vec, Res, alpha, f_t, e);
		for(int i = 0;i<sommet;i++){vec[i] = Res[i];}
	for(int i = 0 ; i < sommet ; i++) {printf(" %lf ",Res[i]);}
		printf("\n");
		j++;
	}while(compare(res_1,Res,sommet,precision));

		FILE *fic = fopen("vec.txt","w+");
		
		
		for(int i = 0 ; i < sommet ; i++) {fprintf(fic," %lf ",Res[i]);}
		printf("\n");

		printf("nbr iteration = %d",j);
		
	//max(F,sommet);
		t2 = clock();
		printf("time : %ld",(t2-t1)/CLOCKS_PER_SEC);
	free(Res);
	//free(tabSommet);
	free(e);
	free(vec);
	free(liste_succ);
	free(res_1);
	free(f_t);
	free(tabSommet);
  return 0;
}