/*
Name: Matt Favela
Student ID #: 2390407
Email: mfavela@chapman.edu
Course Number and Section: CPSC350-03
Assignment: PA2

Brief Overview:
This file is the impelmentation of the file processor class. All we really do here
is take in an input file name and output file name, take input from input file, then
run simulation

High Level Decisions Used:
N/
*/

#include "FileProcessor.h"
#include "Game.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std; 

FileProcessor::FileProcessor(){

}

void FileProcessor::processFile(std::string inputFileName, std::string outputFileName){
    std::fstream inputFile;
    std::string currentLine;
    int values[8] = { 0 }; 

    inputFile.open(inputFileName, ios::in);
    int i = 0;
    for(std::string line; getline(inputFile, line);){
        values[i] = stoi(line);
        i++;
    }
    inputFile.close();
    game = new Game(values[0], values[1], values[2], values[3], values[4], values[5], values[6], values[7], outputFileName);
    game->SimulateGameplay();
}