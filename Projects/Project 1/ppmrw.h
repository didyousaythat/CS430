
#ifndef PPMRW_H
#define PPMRW_H

//error message 
//error message constants
typedef enum paramErrorCodes
{
   NO_ERROR,
   ARGUMENT_NUM_ERROR,
   NO_OUTPUT_FILE_ERROR,
   PPM_TYPE_ERROR,
} paramErrorCodes;

// struct for fileHeader
struct fileHeader
{
   int height;

   int width;

   int ppmType;

};

//file name constants
extern const char INPUT_FILE_NAME[];
extern const char OUTPUT_FILE_NAME[];

//ppm type constants
extern const int PPM3;
extern const int PPM6;


//method prototypes
int validateParams( int num_of_params, char const *argv[] );
void readFileP3(FILE *filePtr, unsigned int *pixmap);
void readFileP6(FILE *filePtr, unsigned int *pixmap);
void writeToP3(FILE *filePtr, unsigned int *pixmap);
void writeToP6(FILE *filePtr, unsigned int *pixmap);
struct fileHeader readHeader(FILE *filePtr);
int validateParams(int argc, char const *argv[] );
void displayErrorMessage(int errorCode);




#endif
