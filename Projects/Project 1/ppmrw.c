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
* Main of our function that converts a P3 to P6, P3 to P3, P6 to P3, P6 to P6
* Params: argv[1] the PPM to convert to, either 3 or 6
*         argv[2] the input file in ppm format
*         argv[3] the output file to be written to
*/
int main(int argc, char const *argv[])
{
    // validate command line arguments
    int errorCode = ppmValidateParams( argc,  argv );
    FILE *outFile;
	
	if( errorCode != NO_ERROR && errorCode != NO_OUTPUT_FILE_ERROR) 
    {
		ppmDisplayErrorMessage(errorCode);
		printf("Program Terminated\n");
		return EXIT_FAILURE; 
	}
	
    //validate output file name or cerate own
	if( errorCode == NO_OUTPUT_FILE_ERROR ) 
    {
		ppmDisplayErrorMessage(errorCode);
        outFile = fopen("output.ppm", WRITE_FILE_FLAG);
	}
    else 
    {
        outFile = fopen(argv[3], WRITE_FILE_FLAG);
    }
    
    // define and decalre variables
    int ppmConversionType = atoi(argv[1]);
    char const *fileName = argv[2];
    unsigned int *pixmap;

    FILE *inFile = fopen(fileName, READ_FILE_FLAG);

    if( inFile == NULL )
    {
        ppmDisplayErrorMessage(INVALID_INPUT_NAME);
        printf("Program Terminated\n\n");
        return EXIT_FAILURE;
    }

    //get and validate header informtion
    FileHeader *header = ppmReadHeader(inFile);
    
    if(header == NULL)
    {
        printf("Program Terminated\n\n");
        return EXIT_FAILURE;
    }

    printf("Converting a P%d ppm file to a P%d ppm file.\n", 
                header->ppmType, atoi(argv[1]) );

    //read
    if(header->ppmType == PPM3)
    { 
        pixmap = ppmReadFileP3(inFile, header);
    }
    else
    {
	   pixmap = ppmReadFileP6(inFile, header);
    }
        
    // write
    if (ppmConversionType == 3)
    {
        ppmWriteToP3(outFile, header,  pixmap);
    }
    else
    {
        ppmWriteToP6(outFile, header, pixmap);
    }
    
    // close files and free memory
    fclose(inFile);
    fclose(outFile);

    free(header);
    free(pixmap);

    // return 0
    printf("Program Terminated\n\n");
    return EXIT_SUCCESS;
}

/* 
* Reads the header of a PPM, validating input, and saving file dimentions
* Params: A pointer the file header
*/
FileHeader *ppmReadHeader(FILE *filePtr)
{
    //initialize variables
    FileHeader *header = malloc(sizeof(FileHeader));
    header->height = 0;
    header->width = 0;
    header->max = 0;
    char ch = 0;
    char dataBuffer[10];
    int widthData = 0;
    int heightData = 0;
    int channelData = 0;
    
    //read the first line of file to determine header
    fscanf(filePtr, "%s\n", dataBuffer);

    //determine ppm type and validity
    if(strcmp(dataBuffer, "P3") != 0 && strcmp(dataBuffer, "P6") != 0)
    {
        //PPM header type error
        ppmDisplayErrorMessage(HEADER_PPM_TYPE_ERROR);
        return NULL;
    }

    //assign type value as int 
    if(strcmp(dataBuffer, "P3") == 0)
    {
        header->ppmType = PPM3;
    }
    else
    {
        header->ppmType = PPM6;
    }
    
    //consume end of line
    ch = fgetc(filePtr);
    
    //loop through rest of header
    while(!feof(filePtr) && header->max == 0)
    {
         //skip comments
         if(ch == '#')
         {
              while (ch != '\n')
              {
                  ch = fgetc(filePtr);
              }
         }

        fscanf(filePtr, "%d", &widthData);
        
        if( fgetc(filePtr) == '\n')
        {
            ppmDisplayErrorMessage(HEADER_DIMENTION_ERROR);
            return NULL;
        }
        
        fscanf(filePtr, "%d", &heightData);
        header->height = heightData;
        header->width = widthData;
        
        fscanf(filePtr, "%d", &channelData);
        header->max = channelData;

        //Check if channel value is higher than max (255)
        if(header->max > 255)
        {
            ppmDisplayErrorMessage(HEADER_MAX_VALUE_ERROR);
            return NULL;
        }
    }
    
    //get final new line char
    ch = fgetc(filePtr);
    return header;
}

/* 
* Reads a PPM3 formated .ppm file.
* Params:  the pointer to the ppm file to be read
*          the file header structs
*/
unsigned int *ppmReadFileP3(FILE *filePtr, FileHeader *header)
{
    // intialize varibles
    int heightIndex;
    int widthIndex;
    int fileHeight;
    int fileWidth;
    int numberOfChannels = 3;
    unsigned int *pixel;
    unsigned int *pixmap;
    int rgbTempVal;

    // declare variables
    fileHeight = header->height;
    fileWidth = header->width;

    // allocate memory for pixmaps
    pixmap = (unsigned int *)malloc(fileHeight * fileWidth * numberOfChannels * sizeof(unsigned int));

    // make a pixel 'iterator'
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
                        
            fscanf(filePtr, "%d\n", &rgbTempVal);
            *pixel = rgbTempVal;
            pixel++;

            fscanf(filePtr, "%d\n", &rgbTempVal);
            *pixel = rgbTempVal;
            pixel++;

        }
    }
    
    return pixmap;
}


/* 
* Reads and converts a PPM6 file to a PPM3 file
* Params:  the pointer to the ppm file to be read
*          the file header structs
*/
unsigned int *ppmReadFileP6(FILE *filePtr, FileHeader *header)
{
    // intialize varibles
    int heightIndex;
    int widthIndex;
    int fileHeight;
    int fileWidth;
    int numberOfChannels = 3;
    unsigned int *pixel;
    unsigned int *pixmap;
    unsigned int rgbBytes;

    // declare variables
    fileHeight = header->height;

    fileWidth = header->width;

    // asssign size
    pixmap = (unsigned int *)malloc(fileWidth * fileHeight * numberOfChannels * sizeof(unsigned int));

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

            *pixel = rgbBytes & 0xff;
            pixel++;

            *pixel = (rgbBytes >> 8) & 0xff;
            pixel++;

            *pixel = (rgbBytes >> 16) & 0xff;
            pixel++;
        }
    }

    return pixmap;
}

/*
* Takes a PPM3 file and writes to a PPM3 format
* Params:  the pointer to the ppm file to be written to
*          the file header structs
*          a pixmap of 
*/
void ppmWriteToP3(FILE *filePtr, FileHeader *header, unsigned int *pixmap)
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
    
    fprintf(filePtr, "P%d\n", PPM3);
    fprintf(filePtr, "%d %d\n", header->width, header->height);
    fprintf(filePtr, "%d\n", header->max);
                	
    // next write body info to file in P3 style
    for(heightIndex = 0; heightIndex < fileHeight; heightIndex++)
    {
        for(widthIndex = 0; widthIndex < fileWidth; widthIndex++)
        {
            fprintf(filePtr, "%d\n", *pixel);
            pixel++;

            fprintf(filePtr, "%d\n", *pixel);
            pixel++;

            fprintf(filePtr, "%d\n", *pixel);
            pixel++;
        }  
    }   
}


void ppmWriteToP6(FILE *filePtr, FileHeader *header, unsigned int *pixmap)
{
    // declare variables
    unsigned int *pixel;
    int heightIndex;
    int widthIndex;
    int fileHeight;
    int fileWidth;
    unsigned int pixelBuffer;
    unsigned int red;
    unsigned int green;
    unsigned int blue;
	
    // set the fileHeight to header info
    fileHeight = header->height;

    fileWidth = header->width;
	
    // set the pixel pointer to pixmap;
    pixel = pixmap;
	
    // first write header info to file
    
        // write the file header
        fprintf(filePtr, "P%d\n", PPM6);
        fprintf(filePtr, "%d %d\n", header->width, header->height);
        fprintf(filePtr, "%d\n", header->max);
	

    // next write body info to file in P6 style converting the ints to bytes
    for(heightIndex = 0; heightIndex < fileHeight; heightIndex++)
    {
        for(widthIndex = 0; widthIndex < fileWidth; widthIndex++)
        {
            // get each of the color values and store them in temp Values
            red = *pixel;

            pixel++;

            green = *pixel;

            pixel++;

            blue = *pixel;

            pixel++;

            // convert to binary and pack them 

            pixelBuffer = 0xff << 24 | blue << 16 | green << 8 | red;

            // finally write to file

            fwrite(&pixelBuffer, 1, 3, filePtr);
            
        }  
    }
}


int ppmValidateParams( int argc, char const *argv[] )
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

void ppmDisplayErrorMessage(int errorCode)
{
	char errorMsgs[10][200] = {
		"No Error",
		"ERROR: Wrong number of command line arguments. The format should" 
        "follow:\n\t<ppmToConvertTo inputFile outputFile>",
		"No output file was provided, data will be "
            "written to output.ppm",
		"ERROR: PPM type to convert to must be either a 3 or a 6",
        "ERROR: PPM type in header file not recognized as P3 or P6",
        "ERROR: Color value in header exceeds max (8-bit)",
        "ERROR: The width and height are not correct",
        "ERROR: There is no file with that name in this directory"};
					
	printf("%s\n", errorMsgs[errorCode] );
}
