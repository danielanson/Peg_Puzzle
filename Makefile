CC=gcc
CFLAGS=-I.

all: peg testpeg

peg: peg.o pegfunc.o
	$(CC) -o peg peg.o pegfunc.o $(CFLAGS)

testpeg: testpeg.o testpegfunc.o
	$(CC) -o testpeg testpeg.o testpegfunc.o $(CFLAGS)

clean:
	rm -f peg testpeg peg.o pegfunc.o testpeg.o testpegfunc.o


