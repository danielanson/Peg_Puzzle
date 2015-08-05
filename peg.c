#include <peg.h>

int main() {

   for (int i=0; i<SIZE; i++) {
      Puzzle p1 = build_Puzzle(i);   
      p1.triangle[2][1] = 0;
      p1.triangle[3][1] = 0;
      p1.triangle[4][1] = 0;
      
      print_triangle(p1);
      
      for (int row=0; row<SIZE; row++) {
         int col = row;
         Jump j = find_jumps(p1, row, col);
	 print_Jump(j);
         while(col != 0) {
            col --;
            Jump j = find_jumps_for_peg(p1, row, col);
	    print_Jump(j);
         }
      } 
   }
}
