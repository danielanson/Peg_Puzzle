#include <stdlib.h>
#include <stdio.h>

#include "testpeg.h"


int main() {

   printf("\nTesting build_Puzzle wiith test_build_Puzzle\n");
   test_build_Puzzle();
   printf("Done testing build_Puzzle with test_build_Puzzle\n\n");

   printf("\nTesting peg_count wih test_peg_count\n");
   test_peg_count();
   printf("Done testing peg_count wih test_peg_count\n\n");

   printf("\nTesting find_jumps_for_peg wih test_find_jumps_for_peg.c\n");
   test_find_jumps_for_peg();
   printf("\nDone testing find_jumps_for_peg wih test_find_jumps_for_peg.c\n");

   printf("\nTesting find_jumps_for_puzzle wih test_find_jumps_for_puzzle.c\n");
   test_find_jumps_for_puzzle();
   printf("\nDone testing find_jumps_for_puzzle wih test_find_jumps_for_puzzle.c\n");

   printf("\nTesting print_Jump wih test_print_Jump.c\n");
   test_print_Jump();
   printf("\nDone testing print_Jump wih test_print_Jump.c\n");

   printf("\nTesting print_Jumps wih test_print_Jumps.c\n");
   test_print_Jumps();
   printf("\nDone testing print_Jumps wih test_print_Jumps.c\n");

   printf("\nTesting make_jump wih test_make_jump.c\n");
   test_make_jump();
   printf("\nDone testing make_jump wih test_make_jump.c\n");

   exit(0);

}
