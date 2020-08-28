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
   
   // declare and instantiate varibles
   unsigned int *pixmap;
   FILE *filePtr;
   // create out file
   FILE *outFile;
   int ppmConversionType = atoi(argv[1]);
   char const *fileName = argv[2];
   
   
   //TODO: verify that a file name was given, otherwise, create one
   char const *outFileName = argv[3];
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

      outFile = fopen(outFileName, "x");
	}
   else 
   {
      outFile = fopen(outFileName, WRITE_FILE_FLAG);
   }
   
   // open file for reading
   filePtr = fopen(fileName, READ_FILE_FLAG);

   // get header information
   FileHeader *header = readHeader(filePtr);
   
   //if receved null pointer
      //end gracefully
   if(header == NULL)
   {
      printf("Header info read error:");
      return 0;
   }
   
   // temp remove
   printf("reading a %d ppm file", header->ppmType);

   // read file depending on type
   if(header->ppmType == PPM3)
   {
      pixmap = readFileP3(filePtr, header);
   }
   else
   {
	   pixmap = readFileP6(filePtr, header);
   }
	

   // convert file to P3
      // function: writeToP3()
   if (ppmConversionType == 3)
   {
      writeToP3(outFile, header,  pixmap);
   }
   // convert file to P6
      // fuction: writeToP6()
   else
   {
      writeToP6(outFile, header, pixmap);
   }
   
   // closed the files and freeded the memory
   fclose(filePtr);

   fclose(outFile);

   free(header);

   free(pixmap);

   // return 0
   return EXIT_SUCCESS;
}

/* Identifies the file and reads the parameters of height, width, and max
*
*
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
   fscanf(filePtr, "%s\n", dataBuffer);

   //determine ppm type and validity
   if(strcmp(dataBuffer, "P3") != 0 && strcmp(dataBuffer, "P6") != 0)
   {
      //PPM header type error
      displayErrorMessage(PPM_HEADER_TYPE_ERROR);
      return NULL;
   }
   //assign type value
   if(strcmp(dataBuffer, "P3") == 0)
   {
      header->ppmType = PPM3;
   }
   else
   {
      header->ppmType = PPM6;
   }
   
   ch = fgetc(filePtr);
   
   //loop through rest of header
   while(!feof(filePtr) && header->max == 0)
   {
       //skip comments
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
         //Check if channel value is higher than max (255)
         if(header->max > 255)
         {
            displayErrorMessage(HEADER_MAX_VALUE_ERROR);
            return NULL;
         }
      }
   }
   
   return header;
   
}


/* Ascii information
*
*
*
*/
unsigned int *readFileP3(FILE *filePtr, FileHeader *header)
{
   // intialize varibles
   int heightIndex;
   int widthIndex;
   int fileHeight;
   int fileWidth;
   unsigned int *pixel;
   unsigned int *pixmap;
   int rgbTempVal;

   // declare variables
   fileHeight = header->height;

   fileWidth = header->width;

   // allocate memory for pixmaps
   pixmap = (unsigned int *)malloc(fileHeight * fileWidth * 3 * sizeof(unsigned int));

   // make a pixel
   pixel = pixmap;

   // read the height and the width of the file and assign to variables
   // make a for loop for height and width
   for (heightIndex = 0; heightIndex < fileHeight; heightIndex++)
   {
      for ( widthIndex = 0; widthIndex < fileWidth; widthIndex++)
      {
         fscanf(filePtr, "%d\n", &rgbTempVal);

         *pixel = rgbTempVal;
         pixel++;
         
         // scan the green pixel and place into the pixel array
         fscanf(filePtr, "%d\n", &rgbTempVal);

         *pixel = rgbTempVal;
         pixel++;

         // scan the blue pixel and place into the pixel array
         fscanf(filePtr, "%d\n", &rgbTempVal);

         *pixel = rgbTempVal;
         pixel++;
      }
   }
   
   // returning the pixmap
   return pixmap;
}


/* Reading the Byte information
*
*
*
*/
unsigned int *readFileP6(FILE *filePtr, FileHeader *header)
{
   // intialize varibles
   int heightIndex;
   int widthIndex;
   int fileHeight;
   int fileWidth;
   unsigned int *pixel;
   unsigned int *pixmap;
   unsigned int rgbBytes;

   // declare variables
   fileHeight = header->height;

   fileWidth = header->width;

   // asssign size
   pixmap = (unsigned int *)malloc(fileWidth * fileHeight * 3 * sizeof(unsigned int));

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
         *pixel = rgbBytes & 0xff;
         pixel++;
         // translate binary to integers and store green pixel

         *pixel = (rgbBytes >> 8) & 0xff;
         pixel++;
         // translate binary to integers and store blue pixel 

         *pixel = (rgbBytes >> 16) & 0xff;
         pixel++;
      }
   }

   // return the pixmap
   return pixmap;
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
   
      // write the file header
      fprintf(filePtr, "P%d\n", header->ppmType);
      fprintf(filePtr, "%d %d\n", header->width, header->height);
      fprintf(filePtr, "%d\n", header->max);
            	
   // next write body info to file in P3 style
   for(heightIndex = 0; heightIndex < fileHeight; heightIndex++)
   {
      for(widthIndex = 0; widthIndex < fileWidth; widthIndex++)
      {
         // writing the red pixel
         fprintf(filePtr, "%d\n", *pixel);
         pixel++;

         // writing the green pixel
         fprintf(filePtr, "%d\n", *pixel);
         pixel++;

         // wirting the blue pixel
         fprintf(filePtr, "%d\n", *pixel);
         pixel++;
      }  
   }   
}

/* write to a file in P6 style
*
*
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
   
      // write the file header
      fprintf(filePtr, "P%d\n", header->ppmType);
      fprintf(filePtr, "%d %d\n", header->width, header->height);
      fprintf(filePtr, "%d\n", header->max);
	

   // next write body info to file in P6 style
   for(heightIndex = 0; heightIndex < fileHeight; heightIndex++)
   {
      for(widthIndex = 0; widthIndex < fileWidth; widthIndex++)
      {
         // convert int to binary
         // byte = pixel;

         fwrite(pixel, 1, 3, filePtr);

         // pixel++;
         
         // byte = *pixel << 8 
         // pixel = 0xff << 24 | blue << 16 | green << 8 | red;

         // fwrite(bytePixel, 1, 3, filePtr)
      }  
   }
}



int validateParams(int argc, char const *argv[] )
{
		
	//check that the correct number of arguments are provided
	if( argc == 3 )
	{
      if( atoi(argv[1]) != PPM3 && atoi(argv[1]) != PPM6)
      {
         return PPM_TYPE_ERROR;
      }
         
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
	char errorMsgs[7][200] = {
		"No Error",
		"Wrong number of command line arguments. The format should follow:\n\n"
			"\t<ppmToConvertTo inputFile outputFile>\n",
		"No output file was provided, data will be written to output.ppm\n",
		"PPM type to convert to must be either a 3 or a 6\n",
      "PPM type in header file not recognized as P3 or P6.",
      "Color value in header exceeds max." };
					
	printf("%s\nProgram terminated.", errorMsgs[errorCode] );
}
