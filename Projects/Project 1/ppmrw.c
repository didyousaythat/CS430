/*
* Program: ppmConverter.c
* Purpose: Convert image back and forth between P3 and P6 ppm formats
* Authors: Richard A. Sansom, Colton, Gage Gabaldon
*/

//define constants
const int ARGUMENT_NUMBER = 4;
const int PPM3 = 3;
const int PPM6 = 6;
const char READ_FILE_FLAG[] = "r";
const char WRITE_FILE_FLAG[] = "w";

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
	
	if( errorCode != NO_ERROR && errorCode != NO_OUTPUT_FILE_ERROR)
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

   FILE *filePtr;
   
   int ppmConversionType = atoi(argv[1]);
   
   char const *fileName = argv[2];
   
   
   //TODO: verify that a file name was given, otherwise, create ones
   char const *outFileName = argv[3];
   
   
   
   // open file for reading
   filePtr = fopen(fileName, READ_FILE_FLAG);

   // get header information
   FileHeader *header = readHeader(filePtr);
   
   //if receved null pointer
      //end gracefully

//   // read file depending on type
//   if(header->ppmType == PPM3)
//   {
//	   readFileP3(filePtr, header, pixmap);
//   }
//   else
//   {
//	   readFileP6(filePtr, header, pixmap);
//   }
//  
//   // create out file
//   FILE outFile;
//	
//   outFile = fopen(outFileName, WRITE_FILE_FLAG);
//
//   if(
//   // convert file to P3
//      // function: writeToP3()
//   if (ppmConversionType == 3)
//   {
//      writeToP3(outFile, pixmap);
//   }
//
//   // convert file to P6
//      // fuction: writeToP6()
//   else
//   {
//      writeToP6(outFile, pixmap);
//   }

   // return 0
   return EXIT_SUCCESS;
}

/*
Identifies the file and reads the parameters of height, width, and max
*/
FileHeader *readHeader(FILE *filePtr)
{
   //initialize variables
   FileHeader *header = malloc(sizeof(FileHeader));
   header->height = 0;
   header->width = 0;
   header->max = 0;
   char ch = 0;
   int value = 0;
   char dataBuffer[100];
   
   //read in first line
   //if not equal to p3 or p6
      //call print error function
      
      //return null pointer

   //read the first line of file to determine header
   fscanf(filePtr, "P%i\n", &value);

   //determine ppm type and validity
   if(value != 3 && value != 6)
   {
      displayErrorMessage(PPM_TYPE_ERROR);
      return NULL;
   }
   //assign type value
   header->ppmType = value;
   
   ch = fgetc(filePtr);
   
   //loop through rest of header
   while(!feof(filePtr) && header->max == 0)
   {
       if(ch == '#')
       {
           do
           {
              ch = fgetc(filePtr);
           } while (ch != '\n');
       }
       
      //assign the width, height, and max with each int encounter
      fscanf(filePtr, "%s", dataBuffer);
      value = atoi(dataBuffer);
      if(header->width == 0)
      {
         header->width = value;
      }
      else if(header->height == 0)
      {
         header->height = value;
      }
      else
      {
         header->max = value;
      }
   }
   
   return header;
   
}


/* Ascii information
*
*
*
*/
void readFileP3(FILE *filePtr, FileHeader *header, unsigned int *pixmap)
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
void writeToP3(FILE *filePtr, FileHeader *header, unsigned int *pixmap)
{
   // declare variables
   unsigned int *pixel;
   int heightIndex;
   int widthIndex;
   int fileHeight;
   int fileWidth;
	
   // set the fileHeight to header info
   fileHeight = header->height;

   fileWidth = header->width;
	
   // set the pixel pointer to pixmap;
   pixel = pixmap;
	
   // first write header info to file
	
      // write the filetype
    
      // write the height and width
	
      // write the channel number
	
   // next write body info to file in P3 style
   
   
}

/* write to a file in P6 style
*/
void writeToP6(FILE *filePtr, FileHeader *header, unsigned int *pixmap)
{
   // declare variables
   unsigned int *pixel;
   int heightIndex;
   int widthIndex;
   int fileHeight;
   int fileWidth;
	
   // set the fileHeight to header info
   fileHeight = header->height;

   fileWidth = header->width;
	
   // set the pixel pointer to pixmap;
   pixel = pixmap;
	
   // first write header info to file
      
      // write the filetype
    
      // write the height and width
	
      // write the channel number
	
   // next write body info to file in P6 style

      // convert int to binary 
	
      // write to file 
	
      // add new line ?
   
}

/* Byte information
*
*
*
*/
void readFileP6(FILE *filePtr, FileHeader *header, unsigned int *pixmap)
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
