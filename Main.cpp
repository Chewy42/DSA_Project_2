/*
Name: Matt Favela
Student ID #: 2390407
Email: mfavela@chapman.edu
Course Number and Section: CPSC350-03
Assignment: PA2

Brief Overview:
This class is what runs the entire simulation by taking in command line arguments then running the file processor method

High Level Decisions Used:
N/A
*/

//Import Requirements
#include "FileProcessor.h"
#include <iostream>

using namespace std;

/*
Name Of Function: main
l
Description of Value Returned: 0 - just ends program

Description of Parameters: argc - argument count | argv - argument value (array)

Description of exceptions thrown: None
*/

int main(int argc, char** argv){
    FileProcessor* fileP = new FileProcessor();
    fileP->processFile(argv[1], argv[2]);
    return 0;
}