/*
Name: Matt Favela
Student ID #: 2390407
Email: mfavela@chapman.edu
Course Number and Section: CPSC350-03
Assignment: PA2

Brief Overview:
This file defines the entire simulation/game

High Level Decisions Used:
N/A
*/

#ifndef LEVEL_H
#define LEVEL_H

//Import Requirements
#include "Mario.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Game
{
    public:
    Game();
    Game(int grid_size, int max_levels, int initial_lives, int probability_for_coin, int probability_for_nothing, int probability_for_goomba, int probability_for_koopatroopa, int probability_for_mushroom, std::string outputFileName);
    virtual ~Game();
    int grid_size;
    int max_levels;
    int current_level;
    int probability_for_coin;
    int probability_for_nothing;
    int probability_for_goomba;
    int probability_for_koopatroopa;
    int probability_for_mushroom;
    int probabilities[5];
    int marioX;
    int marioY;
    int previousX;
    int previousY;
    bool isGameActive;
    int kills;

    std::string outputFileName;
    std::string result;

    Mario* mario;
    char**  grid;
    void SimulateGameplay();
    void CheckIfLost();
    void CheckSpace();
    void SwapSpaces();
    void SetPreviousPosition();
    void ResetPosition();
    void Fight(std::string enemy);
    void BossFight();
    void KillEarned();
    void GainLife();
    void LoseLife();
    void LosePowerLevel(int amount);
    void AdvanceLevel();
    void WinGame();
    void MakeMove();
    void Move();
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    std::string ChooseDirection();
    void CreateGrid();
    void PopulateGrid();
    char PickWhatToPlace();
    char CheckProbabilities(int probabilityNumber);
    char CheckProbabilitiesForEqualChance(int probabilityNumber);
    char CompareProbability(int probability);
    int GenerateRandomNumber(int maxNumber, int minNumber);
    void SortProbabilities();
    void MoveMario();
    void MoveMarioLeft();
    void MoveMarioRight();
    void MoveMarioUp();
    void MoveMarioDown();

    void OutputStringToFile(std::string string);
    void OutputIntToFile(int integer);
    //debugging
    void CommentPosition(std::string direction);
    void CommentGrid();
};

#endif