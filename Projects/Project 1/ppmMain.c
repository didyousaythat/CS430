int main(int argc, char const *argv[]) {

   // initialize varibles
   unsigned int *pixmap;

   // read file save to pixmap
      // function: readFile
   pixmap = readFile(argv[2]);

   // check for what to convert to P3 or P6


   // convert file to P3
      // function: writeToP3()

   // convert file to P6
      // fuction: writeToP6()

   return 0;
}

unsigned int readFile(File *filePtr, int number, char *string){

   // determine if it is p6 or p3
   if(argv[number] == 6)
   {
     // intialize varibles
     const char READ_BYTE_FLAG[] = "rb"

      filePtr = fopen(string, READ_BYTE_FLAG);

      // check if file is found
      if(filePtr != NULL)
      {

      }
      else
      {
        printf("File Not Found: \n");
      }

   }

   if(argv[number] == 3)
   {

      pixmap = (unsigned int *)malloc(width * height * sizeof(int));

   }

   else
   {
      printf("INCORRECT PPM NUMBER ARGUMENT: \n");
   }
}
