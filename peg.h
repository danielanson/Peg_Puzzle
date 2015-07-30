/*
 * peg.h
 */

//  Because the triangle goes from 1 at the top to 5 at the bottom, the
//  triangle can be represented as a 5 X 5 array.  It would be possible
//  to represent the triangle as 5X9 or 9X9 array but it is easily 
//  represented as a partially filled 5X5 array.

#define SIZE 5

/* DATA STRUCTURES */

//  This struct represents the triangle.  It is a 5 X 5 array with an empty
//  peg slot.  Since there are only 5 potential empty slots.  By rotating
//  the triangle 120 degrees, any empty peg can be simulated, we'll call
//  them 0-4 as seen below, T is for taken, or occupied:
//
//      T            T
//     T T           T T
//    T T T    <-->  T T T 
//   T 0 T T         T 0 T T
//  1 2 3 4 T        1 2 3 4 T

typedef struct {
   int triangle[SIZE][SIZE];
   int empty_peg;
} Puzzle;

//  This struct has an array of 6 elements and a counter for possible jumps.
//  For each peg position being evaluated, and to be a valid jump, three
//  things must apply:
//
//  1)  the center peg must be taken or occupied.
//  2)  the peg being accounted for must not be out of the bounds of the array,
//  3)  there must be an empty peg slot at one end of the three provided its
//      counterpart is not out of bounds of the array.
//
//  In the triangle, it looks like this, C being the center peg, as an example,
//  using T for taken or an occupied peg.
//
//      T            T
//     T T           T T
//    1 2 T    <-->  1 2 T
//   0 C 3 T         0 C 3 T
//  T 5 4 T T        T 5 4 T T
//
//  1 | 2
//  ----------
//  0 | T | 3
//  ----------
//    | 5 | 4
//
//  This pattern will be overlayed on each peg to determine where jumps can be
//  made or not.  This also looks like the following matrix:
//
//  1) [x-1][y-1] | 2) [x-1][y] |
//  -------------------------------------------
//  0) [x][y-1]   | C) [x][y]   | 3) [x][y+1]
//  -------------------------------------------
//                | 5) [x+1][y] | 4) [x+1][y+1]
//
//
//  When a jump is made from a line of 3 (1 horizontal axis, 1 vertical axis,
//  and 1 diagonal access) one end and the center must be occupied.  Each of
//  these series of jumps will result in 2 being empty and one being occupied.
//  The pairs are:
//
//  1)  0 <--> 3
//  2)  1 <--> 4
//  3)  2 <--> 5
//
//  The array will simply hold whether a jump is possible from positions 0-5
//  and the total number of possible jumps.

typedef struct {
   int jump[SIZE+1]
   int possible_jumps;
} Jump;

/*
 * FUNCTIONS
 */

//  print_triangle
//  takes in a Puzzle struct and prints the triangle in a pseudo-triangular
//  readible form as opposed to the 5X5 array.

void print_triangle(Puzzle p);

//  As discussed previously, there are only 5 positions in which an empty
//  peg can reside.  All others represent 120 degree rotations.  This function
//  builds a Puzzle struct with a parameter for the empty peg.  The empty pegs
//  are in fixed positins.

Puzzle build_triangle(int empty_peg);

//  This function merely counts the non-empty pegs in a Puzzle.

int peg_count(Puzzle p);
