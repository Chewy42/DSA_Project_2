/*
Name: Matt Favela
Student ID #: 2390407
Email: mfavela@chapman.edu
Course Number and Section: CPSC350-03
Assignment: PA2

Brief Overview:
This file defines the file processor class

High Level Decisions Used:
N/A
*/

#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include "Game.h"
#include <string>

class FileProcessor{
    public:
    FileProcessor();
    ~FileProcessor();
    void processFile(std::string inputFileName, std::string outputFileName);
    private:
    Game* game;
};

#endif