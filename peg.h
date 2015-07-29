/*
 * peg.h
 * definition for Puzzle struct
 * define array SIZE of 5
 */


#define SIZE 5

typedef struct {
   int triangle[SIZE][SIZE];
   int empty_peg;
} Puzzle;

/*
 * Functions
 */

void print_triangle(Puzzle p);
Puzzle build_triangle(int empty_peg);
int peg_count(Puzzle p);
