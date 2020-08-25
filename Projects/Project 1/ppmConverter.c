/*
* Program: ppmConverter.c
* Purpose: Convert image back and forth between P3 and P6 ppm formats
* Authors: Richard A. Sansom, Colton, Gage Gabaldon
*/

//define constants
const char INPUT_FILE_NAME[] = "input.ppm";
const char OUTPUT_FILE_NAME[] = "output.ppm";
const int PPM3 = 3;
const int PPM = 6;

#include <stdlib.h>
#include <stdio.h>

#include "ppmConverter.h"


/*
* Params: argv[1] the PPM to convert to, either 3 or 6
          argv[2] the input file in ppm format
          argv[3] the output file to be written to
*/
int main(int argc, char const *argv[])
{


   // initialize varibles
   unsigned int *pixmap;
   File *filePtr;
   int ppmType = atoi(argv[1]);
   char *fileName = argv[2];

   if(argc != 4)
   {

   }
   // read file save to pixmap
      // function: readFile
   readFile(filePtr, ppmType, fileName, pixmap);

   // check for what to convert to P3 or P6


   // convert file to P3
      // function: writeToP3()

   // convert file to P6
      // fuction: writeToP6()

   return 0;
}

int validateParams( int num_of_params, char const *argv[] )
{
	int ppmType = atoi(argv[1]);
}

/* Ascii information
*
*
*
*/
void readFileP6(File *filePtr, int ppmNumber, char *fileName, unsigned int *pixmap)
{
   // intialize varibles
   const char READ_BYTE_FLAG[] = "rb";
   const int heightIndex;
   const int widthIndex;
   const int fileHeight;
   const int fileWidth;
   const char comment[];
   struct fileHeader fileHeader;

   filePtr = fopen(fileName, READ_BYTE_FLAG);


   // get the file header information
   fileHeader = readHeader(filePtr);

   // declare variables
   heightIndex = fileHeader.height;

   widthIndex = fileHeader.width;

   comment = fileHeader.comment;

   // allocate memory for pixmap
   pixmap = (unsigned int *)malloc(width * height * sizeof(int));

   // make a pixel
   pixel = pixmap;

   // read the height and the width of the file and assign to variables
   // make a for loop for height and width
   for (heightIndex = 0; heightIndex < fileHeight; heightIndex++)
   {
      for ( widthIndex = 0; widthIndex < fileWidth; widthIndex++)
      {
         int ch;

         ch = fgetc(filePtr);

         pixel[heightIndex + widthIndex] = ch;

      }
   }
}

/* Byte information
*
*
*
*/
void readFileP6(File *filePtr, int ppmNumber, char *fileName, unsigned int *pixmap)
{
   // intialize varibles
   const char READ_ASCII_FLAG[] = "r";
   const int heightIndex;
   const int widthIndex;
   const int fileHeight;
   const int fileWidth;
   const char comment[];
   struct fileHeader fileHeader;

   filePtr = fopen(fileName, READ_ASCII_FLAG);

   // read the head information and store in struct
   fileHeader = readHeaderFile(filePtr);

   // declare variables
   heightIndex = fileHeader.height;

   widthIndex = fileHeader.width;

   comment = fileHeader.comment;

   // asssign size
   pixmap = (unsigned int *)malloc(width * height * sizeof(int));

   // make a pixel
   pixel = pixmap;

   // read the height and the width of the file and assign to variables
   // make a for loop for height and width
   for (heightIndex = 0; heightIndex < fileHeight; heightIndex++)
   {
      for ( widthIndex = 0; widthIndex < fileWidth; widthIndex++)
      {
         // initialize int for reading
         int ch;

         // read file and store in ch
         ch = fgetc(filePtr);

         pixel[heightIndex + widthIndex] = ch;
      }
   }

}

/*

*/
fileHeader readHeader(File *filePtr)
{
   // initialize varibles
   int lineCtr = 0;
   int height = 0, width = 0;
   int ch = 0;
   char dataBuffer[100];
   ch = fgetc(filePtr);
   while(filePtr != EOF)
   {
       if(ch == '#')
       {
           while(ch != '\n')
           {

           }
       }
   }
   //fileHeader.height = height;
   //fileHeader.width = width;
   //
}



// CC = gcc
// CFLAGS = -Wall
// RM = rm -f
//
// all: ppmConverter
//
// ppmConverter: ppmConverter.c
// 	$(CC) $(CFLAGS) ppmConverter.c -o ppmConverter
//
// clean:
// 	$(RM) ppmConverter *~
