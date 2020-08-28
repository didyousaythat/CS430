# CS430 PPM Conversion Program
# Authors: 
Colton Barboro (cpb246@nau.edu), Richard Sansom (ras472@nau.edu), Gage Gabaldon (gag252@nau.edu)
# Usage:
This program takes a PPM file, either a PPM3 or PPM6 file, reads it and converts to wither a PPM3 or PPM6. <br />
To use this program, type ./ppmrw in your terminal, followed by the PPM file you want to convert to, and the input file you want to process. <br />
You can add a third argument that dictates the name of the output file to write the results to, but the program will auto generate the output file name if none are given.<br />
The following is an example of what acceptable inputs look like:<br />
./ppmrw 3 input.ppm<br />
./ppmrw 3 input.ppm output.ppm<br />
./ppmrw 6 input.ppm
# Known issues:
  We have taken care of the bugs that we encountered during programming and we currently aren't throwing errors that are unaccounted for.<br />
  We have fixed memory issues that lead to segfaults and have taken care of false positives in program execution.<br />
  As of writing this we do not have unexpected issues in program execution using our tests, nor issues with compiling.
