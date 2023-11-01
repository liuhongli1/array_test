CC=mpicc
CFLAGS=-Wall -g -O0 -fopenmp -m32

main.o: array.c
	$(CC) $(CFLAGS) array.c 

clean:
	rm -rf *.o 
