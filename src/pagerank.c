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
	/*
 	char name[1000] = "";
 	printf("Choose a file to be computed. Here are file available\n");
 	system("ls graph/");
 	int a = scanf("%s",name);
 	printf("%s",name);
 	if(!check_url(name)){
 		char *str_g = malloc(sizeof(char) * strlen(str) + strlen(name));
 		strcpy(str_g,str);
 		strcat(str_g,name);
 		if(!(F = fopen(str_g,"r"))){return 1;}
 		printf("enter precision of convergence\n");
 		int b = scanf("%lf",&precision);
 		printf("\nenter alpha\n");
 		int c = scanf("%lf",&alpha);
 		free(str_g);

 	}else{
 		printf("name not correct");
 		return 1;
 	}
 	*/
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
 	

 	int *liste = malloc(sommet*sizeof(int));
 	for(int i = 0;i<sommet;i++){liste[i] = 0;}

 	int tmp = sommet;
 	int *k = &tmp;
 	for(int i = 0;i<sommet;i++){vec[i] = ((double) 1.0 / (double) sommet );}
 		int cpt = read_txt(f_t,tabSommet,sommet,F,liste);
 	
	t3 = clock();
	printf("Read time : %ld\n",(t3-t1)/CLOCKS_PER_SEC);

	Vector *theta = malloc(sommet*sizeof(Vector));
	for(int i = 0;i<sommet;i++){
		theta[i].val = i+1;
		theta[i].cout = 0.0;
	}
	Vector *w1 = malloc(sommet*sizeof(Vector));
	Vector *v1 = malloc(sommet*sizeof(Vector));
	int y = 0;
	for(int i = 0;i<sommet;i++){
		if(liste[y]-1 == i){
			//printf("dangling node");
			//printf("liste = %d",liste[y]);
			y++;
			w1[i].cout =0.0;
			w1[i].val = tabSommet[i].val;
			v1[i].cout = 0.0;
			v1[i].val = tabSommet[i].val;
		}else{
		w1[i].cout = (double) (1.0 / (double) (sommet) );
		w1[i].val = tabSommet[i].val;
		v1[i].cout = (double) (1.0 / (double) (sommet) );
		v1[i].val = tabSommet[i].val;
		}
	}
	
	Vector *w2 = malloc(sommet*sizeof(Vector));
	Vector *v2 = malloc(sommet*sizeof(Vector));
	
	int z = 0;
	for(int i = 0;i<sommet;i++){

		if(liste[z]-1 == i){
		w2[i].cout = (double) (1.0 / (double) (sommet) );
		w2[i].val = tabSommet[i].val;
		v2[i].cout = (double) (1.0 / (double) (sommet) );
		v2[i].val = tabSommet[i].val;
		z++;
		}else{
			w2[i].cout =0.0;
			w2[i].val = tabSommet[i].val;
			v2[i].cout = 0.0;
			v2[i].val = tabSommet[i].val;
		}
	}

	int x = 0;
	for(int i = 0;i<sommet;i++){

		if(liste[x] == theta[i].val){
				theta[i].cout = 0.0;
				x++;

		}else{
			//printf("liste[%d] = %d 		",i,liste[i]);
				//printf("theta[%d].val = %d\n",i,theta[i].val);
				theta[i].cout = (double) (1.0 / (double) (sommet));
				
		}
	}



	
	
	double theta_k_1_tmp = (double) (1.0 / (double) (sommet) );
	double *theta_k_1 = &theta_k_1_tmp;
	Vector *res_w1 = malloc(sommet*sizeof(Vector));
	Vector *res_v1 = malloc(sommet*sizeof(Vector));
	double *last = malloc(sommet*sizeof(double));
	/* for(int i = 0;i<sommet;i++){
	 	printf("%d ----->  ",tabSommet[i].val);
	 	Sommet *tmp = (&tabSommet[i])->pred;
	 	while(tmp != NULL){
	 		printf("%d -> %lf ",tmp->val,tmp->cout);
	 		tmp = tmp->pred;
	 	}
	 	printf("\n");
	 }*/
	last = multiplication_dangling_version(w1,w2,v1,v2,theta,alpha,sommet,sommet-cpt,tabSommet,tabSommet,e,res_w1,res_v1,theta_k_1,precision,liste);
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