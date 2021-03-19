# PageRank-Currently-Building-
#
#
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

