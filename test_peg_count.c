#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

#include "peg.h"
#include "testpeg.h"


void test_peg_count(void) {
    
    Puzzle p;
    int peg_cnt = 0;

    // Zero out the triangle and ensure it counts zero.
    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            p.triangle[i][j] = 0;
        }
    }
    peg_cnt = peg_count(p);
    assert(peg_cnt == 0);
    printf("Asserted triangle with all 0's counted 0.\n");
    
    // Zero out the triangle except for 1 that is out
    // of bounds and ensure it counts 0.
    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            p.triangle[i][j] = 0;
        }
    }
    p.triangle[0][4] = 1;
    peg_cnt = peg_count(p);
    assert(peg_cnt == 0);
    printf("Asserted triangle with all 0's and a single 1, which\n");
    printf("counted 1.\n");
    
    // Zero out the triangle except for 1 and ensure it counts only one
    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            p.triangle[i][j] = 0;
        }
    }
    p.triangle[0][0] = 1;
    peg_cnt = peg_count(p);
    assert(peg_cnt == 1);
    printf("Asserted triangle with all 0's and a single 1 counted 1.\n");
    
    // Put all 1's in the triangle 
    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            p.triangle[i][j] = 1;
        }
    }
    peg_cnt = peg_count(p);
    assert(peg_cnt == 15);
    printf("Asserted triangle with all 1's counted correctly.\n");

    // Assert when building a puzzle normally, it counts 14.
    p = build_Puzzle(0);
    assert(p.peg_count == 14);
    printf("Asserted when building a puzzle normally, it counts 14.\n");

}
