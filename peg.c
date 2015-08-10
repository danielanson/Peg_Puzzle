#include <peg.h>
#include <stdlib.h>

int main() {

   for(int i=0; i<SIZE; i++) {
      Puzzle p = build_Puzzle(i);   
      find_jumps_for_puzzle(&p);
      recurse(&p);
   }
}
