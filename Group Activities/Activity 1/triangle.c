/* 
 * Package: CS 430 Class Activities
 * Program: triangle.c
 * Purpose: Test breakout groups and print a triangle
 * Author: Richard A. Sansom
 * Date: 8/14/20
 */

#include <stdio.h>
#include <stdlib.h>

int main( int argc, char const *argv[] )
{

    int maxDim = atoi(argv[1]);
    printf("\n");
    //print triangle.  Start at "1" not "0" since the row/col number is how
    //many "X's" will be printed, and make comparisons inclusive to adjust
    //accordingly
    
    int row = 1;
    for(;row <= maxDim; row++ ) {
        
        //the number of X's in row are equal to to the row number iteself,
        //print that many cols
        int col = 1;
        for(; col <= row; col++) {
            printf("X");
        }
        printf("\n");
    }

    //end program
    printf("\n");
    return EXIT_SUCCESS;
}