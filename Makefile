
run:	src/read.c src/pagerank.c src/product.c
		gcc -Ihead/ -c -Wall src/read.c src/pagerank.c src/product.c
		gcc *.o -o pagerank
		./pagerank web4.txt 0.0000001 0.85
clean:	
	rm -f *.o pagerank
