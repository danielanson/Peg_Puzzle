CC=gcc
CFLAGS=-I.

all: testpeg peg

peg: 
	$(CC) -o peg peg.c pegfunc.c

testpeg: 
	$(CC) -o testpeg testpeg.c pegfunc.c test_build_Puzzle.c test_peg_count.c test_find_jumps_for_peg.c \
	      test_find_jumps_for_puzzle.c test_print_Jump.c test_print_Jumps.c test_make_jump.c

clean:
	rm -f peg testpeg

test: testpeg
	./testpeg

run: peg
	./peg

