/*
* Program: ppmConverter.c
* Purpose: Convert image back and forth between P3 and P6 ppm formats
* Authors: Richard A. Sansom, Colton, Gage Gabaldon
*/

//define constants
const int ARGUMENT_NUMBER = 4;
const int PPM3 = 3;
const int PPM6 = 6;
struct FileHeader *header;

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ppmrw.h"


/*
* Params: argv[1] the PPM to convert to, either 3 or 6
          argv[2] the input file in ppm format
          argv[3] the output file to be written to
*/
int main(int argc, char const *argv[])
{
   // validate if given Params are valid
   int errorCode = validateParams( argc,  argv );
	
	if( errorCode != NO_ERROR )
	{
		displayErrorMessage(errorCode);
		
		return EXIT_FAILURE;
	}
	
	if( errorCode == NO_OUTPUT_FILE_ERROR )
	{
		displayErrorMessage(errorCode);
	}

   // initialize varibles
   unsigned int *pixmap;
   const char READ_FILE_FLAG[] = "r";
   FILE *filePtr;
   int ppmConversionType = atoi(argv[1]);
   char const *fileName = argv[2];

   // open file for reading
   filePtr = fopen(fileName, READ_FILE_FLAG);

   // get header information
   *header = readHeader(filePtr);

   // read file depending on type
   if(header->ppmType == PPM3)
   {
	   readFileP3(filePtr, pixmap);
   }
   else
   {
	   readFileP6(filePtr, pixmap);
   }

   // convert file to P3
      // function: writeToP3()
   if (ppmConversionType == 3)
   {
      writeToP3(filePtr, pixmap);
   }

   // convert file to P6
      // fuction: writeToP6()
   else
   {
      writeToP6(filePtr, pixmap);
   }
   

   // return 0
   return 0;
}

/* Ascii information
*
*
*
*/
void readFileP3(FILE *filePtr, unsigned int *pixmap)
{
   // intialize varibles
   int heightIndex;
   int widthIndex;
   int fileHeight;
   int fileWidth;
   unsigned int *pixel;
   int rgbTempVal;

   // declare variables
   heightIndex = header->height;

   widthIndex = header->width;

   // allocate memory for pixmap
   pixmap = (unsigned int *)malloc(widthIndex * heightIndex * sizeof(int));

   // make a pixel
   pixel = pixmap;

   // read the height and the width of the file and assign to variables
   // make a for loop for height and width
   for (heightIndex = 0; heightIndex < fileHeight; heightIndex++)
   {
      for ( widthIndex = 0; widthIndex < fileWidth; widthIndex++)
      {
         // scan the red pixel and place into the pixel array
         fscanf(filePtr, "%d", &rgbTempVal);

         pixel[0] = rgbTempVal;

         // scan the green pixel and place into the pixel array
         fscanf(filePtr, "%d", &rgbTempVal);

         pixel[1] = rgbTempVal;

         // scan the blue pixel and place into the pixel array
         fscanf(filePtr, "%d", &rgbTempVal);

         pixel[2] = rgbTempVal;

         // move the pixel pointer three spaces
         pixel += 3;

      }
   }
}

/* Writes a file that is in p3 format
*
*
*
*/
void writeToP3(FILE *filePtr, unsigned int *pixmap)
{

}

/* Byte information
*
*
*
*/
void readFileP6(FILE *filePtr, unsigned int *pixmap)
{
   // intialize varibles
   int heightIndex;
   int widthIndex;
   int fileHeight;
   int fileWidth;
   unsigned int *pixel;
   unsigned int rgbBytes;

   // declare variables
   heightIndex = header->height;

   widthIndex = header->width;

   // asssign size
   pixmap = (unsigned int *)malloc(widthIndex * heightIndex * sizeof(int));

   // make a pixel
   pixel = pixmap;

   // read the height and the width of the file and assign to variables
   // make a for loop for height and width
   for (heightIndex = 0; heightIndex < fileHeight; heightIndex++)
   {
      for ( widthIndex = 0; widthIndex < fileWidth; widthIndex++)
      {
         // scan bytes and store in rgbBytes
         fread(&rgbBytes, 1, 3, filePtr);

         // translate binary to integers and store red pixel first
         pixel[0] = rgbBytes & 0xff;

         // translate binary to integers and store green pixel

         pixel[1] = (rgbBytes >> 8) & 0xff;

         // translate binary to integers and store blue pixel 

         pixel[2] = (rgbBytes >> 16) & 0xff;

         // move the pixel pointer three spaces
         pixel += 3;
      }
   }

}

/* writes a file to p6 format
*
*
*
*/
void writeToP6(FILE *filePtr, unsigned int *pixmap)
{

}

/*
*
*/
struct FileHeader readHeader(FILE *filePtr)
{
   // initialize varibles
   int lineCtr = 0;
   header->height = 0, header->width = 0;
   int ch = 0;
   char dataBuffer[100];
   ch = fgetc(filePtr);
   while(filePtr != EOF)
   {
       if(ch == '#')
       {
           do
           {
              ch = fgetc(filePtr);
           } while (ch != '\n');
           ch = getc(filePtr);           
       }

       if(fscanf(filePtr, '%d') != 1)
       {
          if(header->width == 0)
          {
             header->width = ch;
          }
       }
   }
   //FileHeader.height = height;
   //FileHeader.width = width;
   //
}

int validateParams(int argc, char const *argv[] )
{
		
	//check that the correct number of arguments are provided
	if( argc == 3 )
	{
		return NO_OUTPUT_FILE_ERROR;
	}
	else if ( argc != ARGUMENT_NUMBER )
	{
		return ARGUMENT_NUM_ERROR;
	}
	
	else if( atoi(argv[1]) != PPM3 && atoi(argv[1]) != PPM6)
	{
		return PPM_TYPE_ERROR;
	}
	else
	{
		return NO_ERROR;
	}

}

void displayErrorMessage(int errorCode)
{
	char errorMsgs[6][200] = {
		"No Error",
		"Wrong number of command line arguments. The format should follow:\n\n"
			"\t<ppmToConvertTo inputFile outputFile>\n",
		"No output file was provided, data will be written to output.ppm\n",
		"PPM type to convert to must be either a 3 or a 6\n" };
					
	printf("%s\nProgram terminated.", errorMsgs[errorCode] );
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
