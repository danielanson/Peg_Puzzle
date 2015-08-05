#include <peg.h>
#include <stdio.h>

/*
 * pegfunc.c
 */

Puzzle build_Puzzle(int empty_peg) {
   Puzzle p;
   p.empty_peg = empty_peg;

   // Initialize all slots in the array to -1
   for(int row=0; row<SIZE; row++) {
      for(int col=0; col<SIZE; col++) {
	 p.triangle[row][col] = -1;
      }
   }

   for (int row=0; row<SIZE; row++) {
      p.triangle[row][row] = 1;
      int column = row;
      while(column != 0) {
         column --;
	 p.triangle[row][column] = 1;
      }
   }
   switch(p.empty_peg) {
      case 0:
         p.triangle[3][1] = 0;
	 break;
      case 1:
         p.triangle[4][0] = 0;
	 break;
      case 2:
         p.triangle[4][1] = 0;
	 break;
      case 3:
         p.triangle[4][2] = 0;
	 break;
      case 4:
         p.triangle[4][3] = 0;
	 break;
      default:
	 break;
   }
   return p;
}

void print_triangle(Puzzle p) {
   printf("\n");
   printf("     %d\n\n", p.triangle[0][0]);
   printf("    %d %d\n\n", p.triangle[1][0], p.triangle[1][1]);
   printf("   %d %d %d\n\n", p.triangle[2][0], p.triangle[2][1], p.triangle[2][2]);
   printf("  %d %d %d %d\n\n", p.triangle[3][0], p.triangle[3][1], 
		               p.triangle[3][2], p.triangle[3][3]);
   printf(" %d %d %d %d %d\n\n", p.triangle[4][0], p.triangle[4][1], p.triangle[4][2],
		                 p.triangle[4][3], p.triangle[4][4]);
   
   printf("Peg count is %d\n", peg_count(p));
   printf("Starting empty peg was %d\n\n", p.empty_peg);
}

int peg_count(Puzzle p) {
   int peg_count = 0;
   for (int row=0; row<SIZE; row++) {
      if (p.triangle[row][row] == 1) {
	 peg_count++;
      }
      int column = row;
      while(column != 0) {
         column --;
	 if (p.triangle[row][column] == 1) {
	    peg_count++;
	 }
      }
   }
   return peg_count;
}

Jump find_jumps_for_peg(Puzzle p, int row, int col) {

   Jump j;
   int pegs[] = {0, 0, 0, 0, 0, 0};
   int temp_row = 0, temp_col = 0, *ptr;

   // Initialize the Jump struct
   j.xy[0] = row;
   j.xy[1] = col;
   for (ptr = &j.jump[0]; ptr < &j.jump[JUMPSIZE]; ptr++) {
      *ptr = 0;
   }
   j.possible_jumps = 0;

   // The points of the triangle can never be jumped so instantly return
   // the empty Jump struct.
   if ((row==0 && col==0) || (row==4 && col==0) || (row==4 && col==4)) {
      return j;
   }
   // If the [x,y] peg slot is empty, we can't make a jump so return.
   if (p.triangle[row][col] == 0) {
      return j;
   }
   
   for (int count=0; count<JUMPSIZE; count++) {
      ptr = &pegs[count];
      switch(count) {
         case 0:
            temp_row = row;
            temp_col = col - 1;
	    break;
         case 1:
            temp_row = row - 1;
            temp_col = col - 1;
	    break;
         case 2:
            temp_row = row - 1;
            temp_col = col;
	    break;
         case 3:
            temp_row = row;
            temp_col = col + 1;
	    break;
         case 4:
            temp_row = row + 1;
            temp_col = col + 1;
	    break;
         case 5:
            temp_row = row + 1;
            temp_col = col;
            break;
      }
      // Each of the 6 positions are marked -1, 0, or 1.  Out of bounds,
      // empty, or occupied respectively.
      if ((temp_row<0) || (temp_col<0) || (temp_row>=SIZE) || (temp_col>=SIZE)) {
         *ptr = -1;
      } else {
	 *ptr = p.triangle[temp_row][temp_col];
      }
   }

   // Now we determine jumps from positions 0, 1, and 2
   for (int i=0; i<SIZE-1; i++) {
      ptr = &j.jump[i];
      if ((pegs[i] == -1) || (pegs[i+3] == -1)) {
         *ptr = 0;
      }
      if ((pegs[i] == 1) && (pegs[i+3] == 0)) {
         *ptr = 1;
	 j.possible_jumps ++;
      }
      ptr ++;
   }

   // Now we determine jumps from positions 3, 4, and 5
   for (int i=SIZE; i>=3; i--) {
      ptr = &j.jump[i];
      if ((pegs[i] == -1) || (pegs[i-3] == -1)) {
         *ptr = 0;
      }
      if ((pegs[i] == 1) && (pegs[i-3] == 0)) {
         *ptr = 1;
	 j.possible_jumps ++;
      }
      ptr --;
   }
   return j;
}

void print_Jump(Jump j) {
   int *ptr;
   printf("Coordinates:  %d,%d\n", j.xy[0], j.xy[1]);
   printf("Possible Jumps:  %d\n", j.possible_jumps);
   printf("Jumps:  ");
   for (ptr = &j.jump[0]; ptr < &j.jump[JUMPSIZE]; ptr ++) {
      printf("%d", *ptr);
   }
   printf("\n\n");
}


