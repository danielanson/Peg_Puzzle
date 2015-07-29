CC=gcc
CFLAGS=-I.

peg: peg.o pegfunc.o
	$(CC) -o peg peg.o pegfunc.o $(CFLAGS)

clean:
	rm -f peg.o pegfunc.o peg

