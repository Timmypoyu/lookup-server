CC = gcc
CXX = g++

CFLAGS = -g -Wall 
CXXFLAGS = -g -Wall
LDFLAGS = -g 

http-client: http-client.c

.PHONY: clean 
clean:
	rm -f *.o *~ a.out core http-client *.html

.PHONY: all
all: clean http-client
