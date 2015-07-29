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
