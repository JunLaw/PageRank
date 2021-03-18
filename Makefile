
run:	src/read.c src/pagerank.c src/product.c
		gcc -Ihead/ -c -Wall src/read.c src/pagerank.c src/product.c
		gcc *.o -o pagerank
clean:	
	rm -f *.o pagerank
