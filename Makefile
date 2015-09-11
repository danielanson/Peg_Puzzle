CC=gcc
CFLAGS=-I.

all: testpeg peg

peg: peg.c pegfunc.c
	$(CC) -o peg peg.c pegfunc.c

testpeg: testpeg.c testpegfunc.c
	$(CC) -o testpeg testpeg.c testpegfunc.c pegfunc.c

clean:
	rm -f peg testpeg peg.o pegfunc.o testpeg.o testpegfunc.o


