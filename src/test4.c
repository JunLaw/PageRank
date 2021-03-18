#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAX_SIZE 360000


typedef struct somm{
  int val;
  double cout;


}Arc;





void fetchLine(FILE* fp, char** line, size_t* len)
{
    char chunk[256];
    if(line == NULL || len == NULL || fp == NULL)
    {
        printf("You fucked up somewhere in ReadLineArc\n");
        exit(EXIT_FAILURE);
    }

    if(*line == NULL || *len < sizeof chunk)
    {
        *len = sizeof chunk;
        *line = malloc(*len);
        if(*line == NULL)
            {
                printf("Failed to allocate memory\n");
                exit(EXIT_FAILURE);
            }
    }
    (*line)[0] = '\0';
    size_t len_used =strlen(*line);
    size_t chunk_used =strlen(chunk);
    while(fgets(chunk, sizeof chunk, fp) != NULL)
    {
        len_used =strlen(*line);
        chunk_used =strlen(chunk);

        if(*len - len_used < chunk_used)
        {
            if(*len > MAX_SIZE / 2)
            {
                printf("Stop trying to shove 131K+ chars in the memory you wonderful person (just go to the top and change MAX_SIZE)\n");
                exit(EXIT_FAILURE);
            }
            else
                *len *= 2;
            if((*line = realloc(*line, *len)) == NULL)
            {
                printf("Failed to [RE]allocate memory\n");
                exit(EXIT_FAILURE);
            }
        }
            memcpy(*line + len_used, chunk, chunk_used);
            len_used += chunk_used;
            (*line)[len_used] = '\0';
            if((*line)[len_used - 1] == '\n')
            {
                //printf("CRLF has been found\n");
                break;
            }
    }
        //printf("[IN]String read <%s>\n", *line);
}

size_t fetchString(char* line, size_t totalLen, size_t startingPos, char** subString)
{

  size_t currentPos = startingPos;
  while(!isspace(line[currentPos]) && currentPos < totalLen)
  {
      currentPos++;
  }
  int len = currentPos - startingPos;
  //printf("len<%d> currentPos<%d> startingPos<%d>\n", len, currentPos, startingPos);
  //TO be safe
  if(len == 0)
  {
    printf("currentPos = startingPos in fetchStringID\n");
    exit(EXIT_FAILURE);
  }
  //We need one more byte to allow space for the terminating '\0'
  *subString = malloc(len + 1);
  if(*subString == NULL){
      printf("Failed to allocate memory\n");
      exit(EXIT_FAILURE);
  }
  strncpy(*subString, line + startingPos, len);
  (*subString)[len] = '\0';
  //set the pos to the next value
  while(isspace(line[currentPos]) && currentPos < totalLen)
  {
    currentPos++;
  }
  //printf("Line is: <%s>\nsubLine is <%s>\n", line, *subString);
  //printf("currentPos= <%d>\n\n", currentPos);

  return currentPos;
}

/*
  Uses fetchString to get a block of chars and converts it to a double while progressing the readingHead startingPos
*/
double fetchDouble(char* line, size_t totalLen, size_t* startingPos)
{
    double result;
    char* subString;
    char* tailptr;

    *startingPos = fetchString(line, totalLen, *startingPos, &subString);
    result = strtod(subString, &tailptr);

    free(subString);
    return result;
}



int fetchInt(char* line, size_t totalLen, size_t* startingPos)
{
    int result;
    char* subString;

    *startingPos = fetchString(line, totalLen, *startingPos, &subString);
    result = atoi(subString);

    free(subString);
    return result;
}

/*
    Reads one line of the TXT Matrix
    Creates and place all the new arcs inside the hollow matrix
*/
int readLineArc(FILE* fp, int currentVertex, Arc** T, int* f,int *liste_succ)
{

    int amArcRead = 0;
    int amArcToRead = 0;
    int vertexRead = 0;
    int destVertex = 0;
    double weight = 0.0;

    char* line = NULL;
    size_t len = 0;
    size_t startingPos = 0;
    fetchLine(fp, &line, &len);
    //printf("[OUT]String read <%s>\n", line);

    //Reads the vertex ID
    vertexRead = fetchInt(line, len, &startingPos);
    printf("VertexID <%d>\n", vertexRead);

    //Reads the Arc amount
    amArcToRead = fetchInt(line, len, &startingPos);
    if(amArcToRead == 0)
      {  f[currentVertex-1] = 1;}
    printf("Amount of Arcs to read <%d>\n", amArcToRead);
    T[vertexRead-1] = malloc(amArcToRead * sizeof(Arc));
    //liste_succ[vertexRead-1] = amArcToRead;
    //Reads and creates all the Arc of the line
    while(amArcRead < amArcToRead)
    {
        destVertex = fetchInt(line, len, &startingPos);
        printf("destVertex <%d>", destVertex);
        weight = fetchDouble(line, len, &startingPos);
        printf(" for a weight of <%f>\n", weight);

        Arc tmp; 
        tmp.val = destVertex;
        tmp.cout =  weight;
       T[currentVertex][amArcRead] = tmp;

        amArcRead++;
    }

    free(line);
    //printf("Line Over\n\n");
    return amArcRead;
}





int main(){
  FILE *F;
  clock_t t1, t2;
 float temps;
    t1 = clock();
  if(!(F = fopen("Stanford_BerkeleyV2.txt","r"))){
    printf("null");
    return 1;
    
  }
  char nbrsommet[10000]="";
  char nbrarcs[10000]="";
  int numsommet,nbrsucc,num;
  int sommet;
  int arcs;
  int *f = malloc(sommet*sizeof(int));
   fgets(nbrsommet,10000,F);
   fgets(nbrarcs,10000,F);
   sscanf(nbrsommet,"%d",&sommet);
   sscanf(nbrarcs,"%d",&arcs);
   int *liste_succ = malloc(sommet*sizeof(int));

   Arc **tabSommet = malloc (sommet * sizeof(Arc*));
   for(int i = 0;i<sommet;i++){
   // printf(" oui");
    //printf("i = %d\n",i);
   readLineArc(F,i,tabSommet,f,liste_succ);
 }
 t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps = %f\n", temps);
/*
   for(int i = 0;i< sommet;i++){
    //printf("i = %d\n",i);
    for(int j = 0;j<liste_succ[i];j++){

        printf(" tabSommet[%d][%d] = %d, %lf \n",i,j,tabSommet[i][j].val,tabSommet[i][j].cout);
        
    }
    printf("\n");
   }
*/

}