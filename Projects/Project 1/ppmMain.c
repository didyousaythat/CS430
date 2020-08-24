int main(int argc, char const *argv[]) {

   // initialize varibles


   // need a check for error if not 8 bit per channel

   // check if command line is right

     // check if arg[1] is 3 or 6 else return error

     // check if file != NULL save to fileptr
        // function: fopen


   // check what conversion we are doing

      // if argv == 3 then convert to ppm 3

         // read file save to buffer
            // function:


         // convert file to P3
            // function: convertToP3()

         // write file to output.ppm
            // function: writeToFile();

   // end ppm3

   // if argv == 6 then convert to ppm 6

      // read file save to buffer
         // function:

      // convert file to P3
         // function: convertToP3()

      // write file to output.ppm
         // function: writeToFile();

   // end ppm6

   return 0;
}
