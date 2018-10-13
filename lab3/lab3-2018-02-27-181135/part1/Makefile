CC = gcc
CFLAGS = -Wall -g
LFLAGS = -g 

mylist-test: libmylist.a mylist-test.o 
	gcc mylist-test.o -L. -lmylist -o mylist-test  

libmylist.a: mylist.o 
	ar rc libmylist.a mylist.o
	ranlib libmylist.a

mylist.o : mylist.c mylist.h 

mylist-test.o : mylist-test.c mylist.h

.PHONY: clean 
clean: 
	rm -f *.o mylist a.out libmylist.a mylist-test
