//error message constants
typedef enum paramErrorCodes
{
    PPM_TYPE_ERROR = 1,
	NO_INPUT_FILE_ERROR,
	INPUT_FILE_NAME_ERROR,
	NO_OUTPUT_FILE_ERROR,
	OUTPUT_FILE_NAME_ERROR;
} paramErrorCodes;

// struct for fileHeader
struct fileHeader
{
   int height;

   int width;

   // comment set to length
   char comment[60];
}
//file name constants
extern const char INPUT_FILE_NAME[];
extern const char [];

//ppm type constants
extern const int PPM3;
extern const int PPM6;

//file definitions
