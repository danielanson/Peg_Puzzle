/*
 * peg.h
 */

//  Because the triangle goes from 1 peg at the top to 5 pegs at the bottom,
//  the triangle can be represented as a 5 X 5 array.  It would be possible
//  to represent the triangle as 5X9 or 9X9 array but it is easily 
//  represented as a partially filled 5X5 array.

#define COORDINATES 2
#define JUMPSIZE 6
#define PEGS 15
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
   int xy[COORDINATES];
   int jump[JUMPSIZE];
   int possible_jumps;
} Jump;

typedef struct {
   int triangle[SIZE][SIZE];
   int empty_peg;
   int all_possible_jumps;
   Jump jumps[PEGS];
} Puzzle;

//  This struct has an array of 6 elements and a counter for possible jumps.
//  For each peg position being evaluated, and to be a valid jump, three
//  things must apply:
//
//  1)  the center peg must be taken or occupied.
//  2)  the peg starting a jump must not be out of the bounds of the Puzzle.
//  3)  there must be an empty peg slot to jump into directly across from the
//      jumping peg jumping over the center peg and the destination must not
//      be outside the bounds of the Puzzle.
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
//  0 | C | 3
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
//  and 1 diagonal axis), one end and the center must be occupied.  Each of
//  these series of jumps will result in 2 being empty and one being occupied.
//  The pairs are:
//
//  1)  0 <--> 3
//  2)  1 <--> 4
//  3)  2 <--> 5
//
//  The array will simply hold whether a jump is possible from positions 0-5
//  and the total number of possible jumps.

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

Puzzle build_Puzzle(int empty_peg);

//  This function merely counts the non-empty pegs in a Puzzle.

int peg_count(Puzzle p);

// This function takes in and [x,y] coordinate and counts the jumps around it.
// It will be using the methodology described above.  There will be three
// possible answers:
//
// 1)  1:  A jump is possible
// 2)  0:  A jump is not possible
// 3)  -1:  Out of Bounds

Jump find_jumps_for_peg(Puzzle p, int row, int col);
void find_jumps_for_puzzle(Puzzle *p);
void print_Jump(Jump j);
void print_Jumps(Puzzle p);

