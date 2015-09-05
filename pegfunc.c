#include <stdio.h>
#include <stdbool.h>
#include "peg.h"

/*
 * pegfunc.c
 */

// Builds the initial Puzzle struct but doesn't fill in the Jump array.  I
// wanted that to be a function with a pointer so I can recurse a bit easier.
Puzzle build_Puzzle(int empty_peg) {

   Puzzle p;
   p.empty_peg = empty_peg;

   // Initialize all slots in the array to -1
   for(int row=0; row<SIZE; row++) {
      for(int col=0; col<SIZE; col++) {
	 p.triangle[row][col] = -1;
      }
   }

   // Here's where we fill in the triangle, This loop pair traverses the
   // triangle pretty cleanly so you'll see it a few more times in the code.
   for (int row=0; row<SIZE; row++) {
      p.triangle[row][row] = 1;
      int column = row;
      while(column != 0) {
         column --;
	 p.triangle[row][column] = 1;
      }
   }

   // Depending on the starting hole, 5 separate cases.
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
   p.peg_count=peg_count(p);
   return p;
}

void print_triangle(Puzzle p) {

   printf("\n");
   printf("     %d\n\n", p.triangle[0][0]);
   printf("    %d %d\n\n", p.triangle[1][0], p.triangle[1][1]);
   printf("   %d %d %d\n\n", p.triangle[2][0], p.triangle[2][1], 
		             p.triangle[2][2]);
   printf("  %d %d %d %d\n\n", p.triangle[3][0], p.triangle[3][1], 
		               p.triangle[3][2], p.triangle[3][3]);
   printf(" %d %d %d %d %d\n\n", p.triangle[4][0], p.triangle[4][1], 
		                 p.triangle[4][2], p.triangle[4][3], 
				 p.triangle[4][4]);
   printf("Peg count is %d\n", p.peg_count);
   printf("Starting empty peg was %d\n", p.empty_peg);
   printf("Total possible jumps:  %d\n\n", p.all_possible_jumps);
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

// Wanted to keep this function out of the build_Puzzle function because we
// will be using this function for recursion.
void find_jumps_for_puzzle(Puzzle *p) {

   p->all_possible_jumps = 0;
   p->peg_count = peg_count(*p);
   int count = 0;
   for(int row=0; row<SIZE; row++) {
      Jump j = find_jumps_for_peg(*p, row, row);
      p->jumps[count] = j;
      p->all_possible_jumps += j.possible_jumps;
      count ++;
      int column = row;
      while(column != 0) {
	 column --;
         Jump k = find_jumps_for_peg(*p, row, column);
	 p->jumps[count] = k;
         p->all_possible_jumps += k.possible_jumps;
	 count ++;
      }
   }
}

// Finds the jump for a single peg.
Jump find_jumps_for_peg(Puzzle p, int row, int col) {

   Jump j;
   int positions[] = {0, 0, 0, 0, 0, 0};
   int temp_row = 0, temp_col = 0, *ptr;

   // Initialize the Jump struct
   j.xy[0] = row;
   j.xy[1] = col;
   for (ptr = &j.jump[0]; ptr < &j.jump[JUMPSIZE]; ptr++) {
      *ptr = 0;
   }
   j.possible_jumps = 0;
   j.is_empty = false;

   // The points of the triangle can never be jumped so instantly return
   // the empty Jump struct.  It can however be empty so check for that.
   if ((row==0 && col==0) || (row==4 && col==0) || (row==4 && col==4)) {
      if (p.triangle[row][col] == 0) {
         j.is_empty = true;
      }
      return j;
   }

   // If the [x,y] peg slot is empty, we can't make a jump so return.
   if (p.triangle[row][col] == 0) {
      j.is_empty = true;
      return j;
   }
   
   for (int count=0; count<JUMPSIZE; count++) {
      ptr = &positions[count];
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
   for (int i=0; i<SIZE-2; i++) {
      ptr = &j.jump[i];
      if ((positions[i] == -1) || (positions[i+3] == -1)) {
         *ptr = 0;
      }
      if ((positions[i] == 1) && (positions[i+3] == 0)) {
         *ptr = 1;
	 j.possible_jumps ++;
      }
      ptr ++;
   }

   // Now we determine jumps from positions 3, 4, and 5
   for (int i=SIZE; i>=3; i--) {
      ptr = &j.jump[i];
      if ((positions[i] == -1) || (positions[i-3] == -1)) {
         *ptr = 0;
      }
      if ((positions[i] == 1) && (positions[i-3] == 0)) {
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
   printf("is_empty:  %d\n", j.is_empty);
   printf("Jumps:  ");
   for (ptr=&j.jump[0]; ptr<&j.jump[JUMPSIZE]; ptr++) {
      printf("%d", *ptr);
   }
   printf("\n\n");
}

void print_Jumps(Puzzle p) {

   Jump *jptr;
   for(jptr = &p.jumps[0]; jptr<&p.jumps[PEGS]; jptr++) {
      print_Jump(*jptr);
   }
}

void make_jump(Puzzle *p, Jump *j, int position) {

   // peg being jumped from j-xy[]
   int row=j->xy[0], col=j->xy[1];
   
   if(j->is_empty==true) {
      return;
   }

   // takes care of emptying the middle peg
   p->triangle[row][col] = 0;

   // Clears one and fills the other in combination to define a jump.  Middle
   // peg cleared, and position is emptied.  Complimentary peg to position is
   // then filled.
   switch(position) {
      case 0:
         p->triangle[row][col-1]=0;         
         p->triangle[row][col+1]=1;
         break;
      case 1:
         p->triangle[row-1][col-1]=0;
         p->triangle[row+1][col+1]=1;
         break;
      case 2:
         p->triangle[row-1][col]=0;
         p->triangle[row+1][col]=1;
         break;
      case 3:
         p->triangle[row][col+1]=0;
         p->triangle[row][col-1]=1;         
         break;
      case 4:
	 p->triangle[row+1][col+1]=0;
         p->triangle[row-1][col-1]=1;
         break;
      case 5:
         p->triangle[row+1][col]=0;
         p->triangle[row-1][col]=1;
         break;
   }
   p->peg_count--;
}

void recurse(Puzzle *p) {
 
   for(Jump *jptr=&p->jumps[0]; jptr<&p->jumps[PEGS]; jptr++) {
      for(int i=0; i<JUMPSIZE; i++) {
         if(jptr->jump[i]==1) {
	    p->peg_count = peg_count(*p);
	    if(p->peg_count == 1) {
	       printf("Solution Found!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	       print_triangle(*p);
	    } else {
               make_jump(p, jptr, i);
               find_jumps_for_puzzle(p);
	       Puzzle newp = *p;
	       printf("Peg Count: %d\n", peg_count(*p));
	       recurse(&newp);
	    }
         }
      }
   }
}

