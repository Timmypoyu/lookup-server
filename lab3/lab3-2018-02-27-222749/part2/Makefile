CC = gcc 
CFLAGS = -Wall -g -I../part1
LDFLAGS = -g -L../part1 -lmylist 

revecho: revecho.o 
	gcc -g revecho.o -L../part1 -lmylist -o revecho
revecho.o: revecho.c 

.PHONY: clean
clean: 
	rm -f *.o revecho a.out
