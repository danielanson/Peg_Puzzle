#include <stdlib.h>
#include <stdio.h>
#include "peg.h"


int main() {

   for(int i=0; i<SIZE; i++) {
      Puzzle p = build_Puzzle(i);   
      find_jumps_for_puzzle(&p);

      printf("Triangle: %d", i);

      recurse(&p);
   }
}
