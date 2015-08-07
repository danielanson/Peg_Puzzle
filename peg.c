#include <peg.h>
#include <stdlib.h>

int main() {

   Puzzle p = build_Puzzle(3);   
   find_jumps_for_puzzle(&p);
   print_triangle(p);

   for(Jump *jptr=&p.jumps[0]; jptr<&p.jumps[PEGS]; jptr++) {
      for(int i=0; i<JUMPSIZE; i++) {
         if(jptr->jump[i]==1) {
	    make_jump(&p, jptr, i);
            find_jumps_for_puzzle(&p);
            print_triangle(p);
	    print_Jumps(p);
	    exit(0); 
         }
      }
   }
}
