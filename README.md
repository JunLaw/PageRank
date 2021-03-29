# PaeRank-Currently-Building-

## An efficient and linear complexity reading of a sparse matrix
## A Google computation of pagerank based on xG = alpha * x * P + [(1-alpha)(1/N) + alpha * (1/N)(x * f^t)]e 
### alpha = initial scalar, N = number of vertices, f^t = dangling node speification vector, e = the 1 column vector

## Compilation
Using Makefile type

> make
> 
> ./pagerank ["name of the file"] ["precision of the convergence"] [alpha]
> 

An example can be run with  

> make run
> 

## graph


a folder that contains text files of web graph example that are formatted and computed with pagerank

## src

C source file

### read.c

#### read_txt

read hypertext graph and convert it into effective data structure (linear complexity)

#### check_url

read "name of the file" and check the correct format of the name return 0 if correct 1 if not

#### compare

convergence function, with the precision stop when reach absolute value precision

