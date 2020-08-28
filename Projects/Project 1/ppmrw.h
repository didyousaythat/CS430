/*
* Header file to accompany ppmrw.c
*/

#ifndef PPMRW_H
#define PPMRW_H

//error messages
typedef enum ParamErrorCodes
{
   NO_ERROR,
   ARGUMENT_NUM_ERROR,
   NO_OUTPUT_FILE_ERROR,
   PPM_TYPE_ERROR,        
   HEADER_PPM_TYPE_ERROR,
   HEADER_MAX_VALUE_ERROR,
   HEADER_DIMENTION_ERROR,
   INVALID_INPUT_NAME,

} ParamErrorCodes;

// struct for fileHeader
typedef struct 
{
   int height;
   int width;
   int ppmType;
   int max;
} FileHeader;

//ppm type constants
extern const int PPM3;
extern const int PPM6;

extern const char READ_FILE_FLAG[];
extern const char WRITE_FILE_FLAG[];


//method prototypes
int ppmValidateParams( int argc, char const *argv[] );

unsigned int *ppmReadFileP3(FILE *filePtr, FileHeader *header);
unsigned int *ppmReadFileP6(FILE *filePtr, FileHeader *header);

void ppmWriteToP3(FILE *filePtr, FileHeader *header, unsigned int *pixmap);
void ppmWriteToP6(FILE *filePtr, FileHeader *header, unsigned int *pixmap);

FileHeader *ppmReadHeader(FILE *filePtr);
void ppmDisplayErrorMessage(int errorCode);

#endif
