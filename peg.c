#include <peg.h>

int main() {

   for (int i=0; i<6; i++) {
      Puzzle p1 = build_triangle(i);   
      print_triangle(p1);
   }
}
