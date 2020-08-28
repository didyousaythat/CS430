
#ifndef PPMRW_H
#define PPMRW_H

//error message 
//error message constants
typedef enum ParamErrorCodes
{
   NO_ERROR,
   ARGUMENT_NUM_ERROR,
   NO_OUTPUT_FILE_ERROR,
   PPM_TYPE_ERROR,
   PPM_HEADER_TYPE_ERROR,
   HEADER_MAX_VALUE_ERROR
} ParamErrorCodes;

// struct for fileHeader
typedef struct
{
   int height;

   int width;

   int ppmType;
   
   int max;

} FileHeader;

//file name constants
extern const char INPUT_FILE_NAME[];
extern const char OUTPUT_FILE_NAME[];

//ppm type constants
extern const int PPM3;
extern const int PPM6;

extern const char READ_FILE_FLAG[];
extern const char WRITE_FILE_FLAG[];


//method prototypes
int validateParams( int num_of_params, char const *argv[] );
unsigned int *readFileP3(FILE *filePtr, FileHeader *header);
unsigned int *readFileP6(FILE *filePtr, FileHeader *header);
void writeToP3(FILE *filePtr, FileHeader *header, unsigned int *pixmap);
void writeToP6(FILE *filePtr, FileHeader *header, unsigned int *pixmap);
FileHeader *readHeader(FILE *filePtr);
int validateParams(int argc, char const *argv[] );
void displayErrorMessage(int errorCode);

#endif
