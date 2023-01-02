/*
Name: Matt Favela
Student ID #: 2390407
Email: mfavela@chapman.edu
Course Number and Section: CPSC350-03
Assignment: PA2

Brief Overview:
This file defines the Mario class along with all its stats, accessors, and mutators

High Level Decisions Used:
N/A
*/


#ifndef MARIO_H
#define MARIO_H

//Import Requirements
#include <string>

class Mario
{
    public:
    Mario();
    Mario(int number_of_lives);
    ~Mario();
    int getNumberOfLives();
    void setNumberOfLives(int lives_amount);
    int getNumberOfCoins();
    void setNumberOfCoins(int coins_amount);
    int getCurrentPowerLevel();
    void setCurrentPowerLevel(int power_level_amount);
    void IncreasePowerLevel(int incrementAmount);
    void DecreasePowerLevel(int decrementAmount);
    void IncrementCoins();
    void ConsumeMushroom();
    void LosePowerLevel();
    void Warp();
    private:
    int number_of_lives;
    int number_of_coins;
    int current_power_level;
};

#endif