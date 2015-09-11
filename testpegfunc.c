#include <stdbool.h>
#include <assert.h>

#include "peg.h"
#include "testpeg.h"


void test_build_Puzzle(void) {

   for (int i=0; i<SIZE; i++) {
      Puzzle p = build_Puzzle(i);
      for (int row=0; row<SIZE; row++) {
         assert(p.triangle[row][row] = 1);
         int column = row;
	 while(column != 0) {
            column --;
            if(row == 3 && column == 1 && i==0 ) {
               assert(p.triangle[3][1] == 0);
	    } else if(row == 4 && column == 0 && i==1) {
               assert(p.triangle[4][0] == 0); 
            } else if(row == 4 && column == 1 && i==2) {
               assert(p.triangle[4][1] == 0); 
            } else if(row == 4 && column == 2 && i==3) {
               assert(p.triangle[4][2] == 0); 
            } else if(row == 4 && column == 3 && i==4) {
               assert(p.triangle[4][3] == 0); 
            } else {
               assert(p.triangle[row][column] == 1);
            }   
         }
      }
   }
}
