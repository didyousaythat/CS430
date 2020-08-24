#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


//Input: 	Width of height of one bar
//Output: 	Use the function from this weeks video to "print' a pattern
//			of 7 bars
			
//Hint: 	Use malloc() to create a pixmap using an array of 
//			uint8_t or unit32_t
int main(int argc, char *argv[]) {
	
    int width = argv[1];
    int height = argv[2];

    int totalLength = width * height;

	uint32_t *pixmap = malloc( totalLength * sizeof( uint32_t ) );
	
}


void print_pixmap( unit32_t *pixmap, int width, int height ) 
{
    for ( int y = 0; y < height; y++ )
    {
        for ( int y = 0; x < width; x++ )
        {
            uint32_t value = pixmap[ (y * width) + x ]
            printf("#%02x%02x%02x",
                    (value >> 24),
                    (value >> 16) & 0xFF,
                    (value >> 8) & 0xFF );
        }
        printf("\n")
    }
}