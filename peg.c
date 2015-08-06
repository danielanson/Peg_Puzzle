#include <peg.h>

int main() {

   Puzzle p = build_Puzzle(3);   
   find_jumps_for_puzzle(&p);
   print_triangle(p);
   print_Jumps(p);
}
