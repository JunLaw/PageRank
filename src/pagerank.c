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
 	int a = 0;
 	int *q = &a;
 	int s = 0;
	char *str = "./graph/";
	int exit = 0;
 	char name[1000] = "";
 	while(exit != 1){
 	system("clear");
 	printf("Choose a file to be computed. Here are file available\n");
 	system("ls graph/");
 	scanf("%s",name);
 	//printf("%s",name);

 	if(!check_url(name)){
 		char *str_g = malloc(sizeof(char) * strlen(str) + strlen(name));
 		strcpy(str_g,str);
 		strcat(str_g,name);
 		if(!(F = fopen(str_g,"r"))){

 			printf("File not found\n");
 		}
 		else{

 			int b,c,d;
 			do{
 				//precision = 0.0;
				
 				printf("enter precision of convergence\n");
 				scanf(" %lf",&precision);
 				//printf("%lf",precision);

 			}while(((b=getchar()) != '\n') && (b != EOF));
 		//printf("b = %d",b);
 			do{

 				printf("enter alpha\n");
 				scanf("%lf",&alpha);
 				//printf("c = %d",c);

 			}while(((c=getchar()) != '\n') && (c != EOF));
 			do{

 				printf("1) Normal Pagerank Computation\n2) Lumping Pagerank Computation  \n");
 				scanf("%d",&s);
 				//printf("s = %d",s);
 			}while((((d=getchar()) != '\n') && (d != EOF)));
 		
 		//printf("d = %d",d);

 		free(str_g);
 		exit = 1;
 	}
 	}else{
 		printf("Name not correct\n");
 		
 	}
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

 	int *liste = malloc(sommet*sizeof(int));
 	for(int i = 0;i<sommet;i++){liste[i] = 0;}

 	for(int i = 0;i<sommet;i++){vec[i] = ((double) 1.0 / (double) sommet );}
 	int cpt = read_txt(f_t,tabSommet,sommet,F,liste);
 	
	t3 = clock();
	printf("Read time : %ld\n",(t3-t1)/CLOCKS_PER_SEC);

	if(s == 2){
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
		
			theta[i].cout = (double) (1.0 / (double) (sommet));
				
		}
	}



	
	//dangling pagerank
	double theta_k_1_tmp = (double) (1.0 / (double) (sommet) );
	double *theta_k_1 = &theta_k_1_tmp;
	Vector *res_w1 = malloc(sommet*sizeof(Vector));
	Vector *res_v1 = malloc(sommet*sizeof(Vector));
	double *last = malloc(sommet*sizeof(double));
	t3 = clock();
	last = multiplication_dangling_version(w1,w2,v1,v2,theta,alpha,sommet,sommet-cpt,tabSommet,tabSommet,e,res_w1,res_v1,theta_k_1,precision,liste,q);
	t2 = clock();
	//printf("q= %d",*q);
	FILE *fic = fopen("vec1.txt","w+");		
	for(int i = 0 ; i < sommet ; i++) {fprintf(fic," %f ",last[i]);}
	
	printf("Pagerank time : %ld\n",(t2-t3)/CLOCKS_PER_SEC);
	
	}else if(s == 1){
	// Normal Pagerank
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
	for(int i = 0 ; i < sommet ; i++) {fprintf(fic," %f ",Res[i]);}
	printf("nbr iteration = %d\n",j);	
	t2 = clock();
	printf("PageRank time : %ld\n",(t2-t3)/CLOCKS_PER_SEC);
	}else{
		printf("not a valid mode");
		return 1;
	}

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