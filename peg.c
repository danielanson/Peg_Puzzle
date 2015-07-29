#include <stdio.h>
#include <peg.h>

void print_triangle(Puzzle p);
Puzzle build_triangle(int empty_peg);
int peg_count(Puzzle p);


int main() {

   for (int i=0; i<6; i++) {
      Puzzle p1 = build_triangle(i);   
      print_triangle(p1);
      printf("Peg count is %d\n", peg_count(p1));
   }
}

Puzzle build_triangle(int empty_peg) {
   Puzzle p;
   p.empty_peg = empty_peg;
   for (int row=0; row<SIZE; row++) {
      p.triangle[row][row] = 1;
      int column = row;
      while(column != 0) {
         column --;
	 p.triangle[row][column] = 1;
      }
   }
   switch(p.empty_peg) {
      case 1:
         p.triangle[3][1] = 0;
	 break;
      case 2:
         p.triangle[4][0] = 0;
	 break;
      case 3:
         p.triangle[4][1] = 0;
	 break;
      case 4:
         p.triangle[4][2] = 0;
	 break;
      case 5:
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
}

int peg_count(Puzzle p) {
   int peg_count = 0;
   for (int row=0; row<SIZE; row++) {
      if (p.triangle[row][row] == 1) {
	 peg_count ++;
      }
      int column = row;
      while(column != 0) {
         column --;
	 if (p.triangle[row][column] == 1) {
	    peg_count ++;
	 }
      }
   }
   return peg_count;
}
