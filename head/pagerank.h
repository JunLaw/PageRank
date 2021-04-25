#ifndef __PAGERANK_H
#define __PAGERANK_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <regex.h>
#include <time.h>
#include <math.h>

typedef struct sommet{
	int val;
	double cout;
	struct sommet *pred;


}Sommet;

typedef struct vector{
	int val;
	int ind;
	double cout;
}Vector;


#endif