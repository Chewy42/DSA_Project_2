/*
Name: Matt Favela
Student ID #: 2390407
Email: mfavela@chapman.edu
Course Number and Section: CPSC350-03
Assignment: PA2

Brief Overview:
This file is the implementation for the entire game/simulation from generating each level to what happens in each interaction

High Level Decisions Used:
A high level decision i used was to break down and simplify my code as much as possible so it is not only easy for
me and other coders to read it, but it would also make debugging and adding in more code extremely easy
*/
#include "Game.h"
#include <ctime>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

/*
Name Of Function: Game constructor

Description of Value Returned:

Description of Parameters:

Description of exceptions thrown: 
*/

Game::Game()
{
    current_level = 0;
    kills = 0;
    isGameActive = false;
}

/*
Name Of Function: Game overloaded constructor

Description of Value Returned:

Description of Parameters: grid size(int)is the size of the MxM of the grid. max levels(int) is the max levels of the entire game. initial lives(int) is the amount of 
lives mario starts out with. all the probability parameters(int) are the probability for each specific thing to show up on a location on the grid.
The output file name (std::string) lets us know what the name of the output file is

Description of exceptions thrown: 
*/
Game::Game(int grid_size, int max_levels, int initial_lives, int probability_for_coin, int probability_for_nothing, int probability_for_goomba, int probability_for_koopatroopa, int probability_for_mushroom, std::string outputFileName)
{
     std::fstream outputFile;
     outputFile.open(outputFileName, ios::out);
     outputFile << "" << endl; 
     outputFile.close();

    this->grid_size = grid_size;
    this->max_levels = max_levels;
    this->probability_for_coin = probability_for_coin;
    this->probability_for_nothing = probability_for_nothing;
    this->probability_for_goomba = probability_for_goomba;
    this->probability_for_koopatroopa = probability_for_koopatroopa;
    this->probability_for_mushroom = probability_for_mushroom;
    probabilities[0] = probability_for_coin;
    probabilities[1] = probability_for_nothing;
    probabilities[2] = probability_for_goomba;
    probabilities[3] = probability_for_koopatroopa;
    probabilities[4] = probability_for_mushroom;
    grid = new char *[grid_size];
    for (int i = 0; i < grid_size; i++)
    {
        grid[i] = new char[grid_size];
        for (int e = 0; e < grid_size; e++)
        {
            grid[i][e] = 'x';
        }
    }
    current_level = 1;
    srand(time(NULL));
    mario = new Mario(initial_lives);
    isGameActive = true;
    kills = 0;
    this->outputFileName = outputFileName;
    result = "";
}

/*
Name Of Function: Game destructor

Description of Value Returned:

Description of Parameters:

Description of exceptions thrown: 
*/
Game::~Game()
{
    delete[] grid;
    if(mario != NULL){
        delete mario;
    }
}

/*
Name Of Function: Simulate Gameplay

Description of Value Returned:

Description of Parameters: 

Description of exceptions thrown: 
*/

void Game::SimulateGameplay(){
    CreateGrid();
    int count = 1;
    while (isGameActive == true)
    {
        result += "Current Level: " + to_string(current_level) + ". Current Position: [" + to_string(marioX) + "," + to_string(marioY) + "]. Mario's Current Power Level: " + to_string(mario->getCurrentPowerLevel()) + " ";
        MakeMove();
        CheckSpace();
        result += "\n";
        OutputStringToFile(result);
        result = "";
        CheckIfLost();
        count++;
        int line_length = 0;
        for (int i = 0; i < grid_size; i++)
        {
            for (int e = 0; e < grid_size; e++)
            {
                if (line_length < grid_size - 1)
                {
                    std::string character(1, grid[i][e]);
                    result += "[" + character + "]";
                    line_length++;
                }
                else
                {
                    std::string character(1, grid[i][e]);
                    result += "[" + character + "]\n";
                    line_length = 0;
                }
            }
        }
        OutputStringToFile(result);
        result = "";
    }
    OutputStringToFile("Mario has saved the Princess!");
    OutputStringToFile("Moves Taken: ");
    OutputIntToFile(count);
} 

/*
Name Of Function: CheckIfLost

Description of Value Returned:

Description of Parameters: 

Description of exceptions thrown: 
*/

void Game::CheckIfLost()
{
    if (mario->getNumberOfLives() <= 0)
    {
        OutputStringToFile("Out of lives, lost game");
        isGameActive = false;
    }
}

/*
Name Of Function: MakeMove

Description of Value Returned:

Description of Parameters: 

Description of exceptions thrown: 
*/
void Game::MakeMove()
{
    std::string direction = ChooseDirection();
    if (direction == "up")
    {
        MoveUp();
       result += ". Direction: UP";
    }
    else if (direction == "down")
    {
        MoveDown();
        result += ". Direction: DOWN";
    }
    else if (direction == "left")
    {
        MoveLeft();
        result += ". Direction: LEFT";
    }
    else
    {
        MoveRight();
        result += ". Direction: RIGHT";
    }
}

/*
Name Of Function: WinGame

Description of Value Returned:

Description of Parameters: 

Description of exceptions thrown: 
*/

void Game::WinGame()
{
    result += ". Mario has defeated the final boss and saved the Princess! ";
    isGameActive = false;
}

/*
Name Of Function: Fight

Description of Value Returned:

Description of Parameters: enemy(std::string). here we pass in a string saying what enemy mario is fighting to carry out the correct battle

Description of exceptions thrown: 
*/

void Game::Fight(std::string enemy)
{
    if (enemy == "goomba")
    {
        int fighting_chance = GenerateRandomNumber(1, 100);
        if (fighting_chance < 80)
        {
            SwapSpaces();
            GainLife();
            result += ". Fought Goomba and Won! Lives after interacting with Goobma: " + to_string(mario->getNumberOfLives()) + ". Coins after interacting with Goomba: " + to_string(mario->getNumberOfCoins());
        }
        else
        {
            LosePowerLevel(1);
            ResetPosition();
            result += ". Fought Goomba and Lost. Staying Put. Lives after interacting with Goobma: " + to_string(mario->getNumberOfLives()) + ". Coins after interacting with Goomba: " + to_string(mario->getNumberOfCoins());
        }
    }
    else if (enemy == "koopa")
    {
        int fighting_chance = GenerateRandomNumber(1, 100);
        if (fighting_chance < 65)
        {
            SwapSpaces();
            GainLife();
            result += ". Fought Koopa and Won! Lives after interacting with Koopa: " + to_string(mario->getNumberOfLives()) + ". Coins after interacting with Koopa: " + to_string(mario->getNumberOfCoins());
        }
        else
        {
            LosePowerLevel(1);
            ResetPosition();
            result += ". Fought Koopa and Lost. Staying Put. Lives after interacting with Koopa: " + to_string(mario->getNumberOfLives()) + ". Coins after interacting with Koopa: " + to_string(mario->getNumberOfCoins());
        }
    }
    else if (enemy == "boss")
    {
        BossFight();
    }
}

/*
Name Of Function: BossFight

Description of Value Returned:

Description of Parameters: 

Description of exceptions thrown: 
*/

void Game::BossFight()
{
    int fighting_chance = GenerateRandomNumber(1, 100);
    if (fighting_chance <= 50)
    {
        if (current_level == max_levels)
        {
            WinGame();
        }
        else
        {
            AdvanceLevel();
        }
    }
    else
    {
        LosePowerLevel(2);
        result += ". Fought Level Boss and Lost. Retrying battle. Lives after interacting with Level Boss: " + to_string(mario->getNumberOfLives()) + ". Coins after interacting with Level Boss: " + to_string(mario->getNumberOfCoins());
        BossFight();
    }
}

/*
Name Of Function: KillEarned

Description of Value Returned:

Description of Parameters: 

Description of exceptions thrown: 
*/

void Game::KillEarned()
{
    kills++;
    if (kills == 7)
    {
        GainLife();
    }
}

/*
Name Of Function: AdvanceLevel

Description of Value Returned:

Description of Parameters: 

Description of exceptions thrown: 
*/

void Game::AdvanceLevel()
{
    current_level++;
    CreateGrid();
}

/*
Name Of Function: LosePowerLevel

Description of Value Returned:

Description of Parameters: amount(int) of power level to decrease by for mario

Description of exceptions thrown: 
*/

void Game::LosePowerLevel(int amount)
{
    mario->setCurrentPowerLevel(mario->getCurrentPowerLevel() - amount);
    if (mario->getCurrentPowerLevel() < 0)
    {
        LoseLife();
        mario->setCurrentPowerLevel(1);
    }
}

/*
Name Of Function: GainLife

Description of Value Returned:

Description of Parameters: 

Description of exceptions thrown: 
*/

void Game::GainLife()
{
    mario->setNumberOfLives(mario->getNumberOfLives() + 1);
}

/*
Name Of Function: LoseLife

Description of Value Returned:

Description of Parameters: 

Description of exceptions thrown: 
*/

void Game::LoseLife()
{
    mario->setNumberOfLives(mario->getNumberOfLives() - 1);
    kills = 0;
    if (mario->getNumberOfLives() < 1)
    {
        isGameActive = false;
    }
}

/*
Name Of Function: ResetPosition

Description of Value Returned:

Description of Parameters: 

Description of exceptions thrown: 
*/

void Game::ResetPosition()
{
    marioX = previousX;
    marioY = previousY;
}

/*
Name Of Function: SwapSpaces

Description of Value Returned:

Description of Parameters: 

Description of exceptions thrown: 
*/

void Game::SwapSpaces()
{
    grid[marioX][marioY] = 'H';
    grid[previousX][previousY] = 'x';
}

/*
Name Of Function: SetPreviousPosition

Description of Value Returned:

Description of Parameters: 

Description of exceptions thrown: 
*/

void Game::SetPreviousPosition()
{
    previousX = marioX;
    previousY = marioY;
}

/*
Name Of Function: CheckSpace

Description of Value Returned:

Description of Parameters: 

Description of exceptions thrown: 
*/

void Game::CheckSpace()
{
    if (grid[marioX][marioY] == 'c')
    {
        SwapSpaces();
        mario->IncrementCoins();
        if(mario->getNumberOfCoins() >= 20){
            GainLife();
            mario->setNumberOfCoins(0);
        }
        result += ". Gained 1 Coin! Lives after interacting with Coin: " + to_string(mario->getNumberOfLives()) + ". Coins after interacting with Coin: " + to_string(mario->getNumberOfCoins());
    }
    else if (grid[marioX][marioY] == 'm')
    {
        SwapSpaces();
        mario->IncreasePowerLevel(1);
        result += ". Mario ate a mushroom! Lives after interacting with Mushroom: " + to_string(mario->getNumberOfLives()) + ". Coins after interacting with Mushroom: " + to_string(mario->getNumberOfCoins());
    }
    else if (grid[marioX][marioY] == 'g')
    {
        Fight("goomba");
    }
    else if (grid[marioX][marioY] == 'k')
    {
        Fight("koopa");
    }
    else if (grid[marioX][marioY] == 'b')
    {
        Fight("boss");
    }
    else if (grid[marioX][marioY] == 'w')
    {
        AdvanceLevel();
        result += ". Mario Warped! Lives after interacting with Warp Pipe: " + to_string(mario->getNumberOfLives()) + ". Coins after interacting with Warp Pipe: " + to_string(mario->getNumberOfCoins());
    }
    else if(grid[marioX][marioY] == 'x')
    {
        SwapSpaces();
        result += ". Position Empty! Lives after interacting with Empty Space: " + to_string(mario->getNumberOfLives()) + ". Coins after interacting with Empty Space: " + to_string(mario->getNumberOfCoins());
    }
}

/*
Name Of Function: MoveUp

Description of Value Returned:

Description of Parameters: 

Description of exceptions thrown: 
*/

void Game::MoveUp()
{
    if (marioX == 0)
    {
        SetPreviousPosition();
        marioX = grid_size - 1;
        CheckSpace();
    }
    else
    {
        SetPreviousPosition();
        marioX--;
        CheckSpace();
    }
}
/*
Name Of Function: MoveDown

Description of Value Returned:

Description of Parameters: 

Description of exceptions thrown: 
*/

void Game::MoveDown()
{
    if (marioX == grid_size - 1)
    {
        SetPreviousPosition();
        marioX = 0;
        CheckSpace();
    }
    else
    {
        SetPreviousPosition();
        marioX++;
        CheckSpace();
    }
}

/*
Name Of Function: MoveLeft

Description of Value Returned:

Description of Parameters: 

Description of exceptions thrown: 
*/

void Game::MoveLeft()
{
    if (marioY == 0)
    {
        SetPreviousPosition();
        marioY = grid_size - 1;
        CheckSpace();
    }
    else
    {
        SetPreviousPosition();
        marioY--;
        CheckSpace();
    }
}

/*
Name Of Function: MoveRight

Description of Value Returned:

Description of Parameters: 

Description of exceptions thrown: 
*/

void Game::MoveRight()
{
    if (marioY == grid_size - 1)
    {
        SetPreviousPosition();
        marioY = 0;
        CheckSpace();
    }
    else
    {
        SetPreviousPosition();
        marioY++;
        CheckSpace();
    }
}

/*
Name Of Function: ChooseDirection

Description of Value Returned: std::string of direction we will go in the next move

Description of Parameters: 

Description of exceptions thrown: 
*/

std::string Game::ChooseDirection()
{
    int direction = GenerateRandomNumber(1, 4);
    if (direction == 1)
    {
        return "up";
    }
    else if (direction == 2)
    {
        return "down";
    }
    else if (direction == 3)
    {
        return "left";
    }
    else
    {
        return "right";
    }
}

/*
Name Of Function: CreateGrid

Description of Value Returned:

Description of Parameters: 

Description of exceptions thrown: 
*/

void Game::CreateGrid()
{
    PopulateGrid();
}

/*
Name Of Function: PopulationGrid 

Description of Value Returned:

Description of Parameters: 

Description of exceptions thrown: 
*/

void Game::PopulateGrid()
{
    for (int i = 0; i < grid_size; i++)
    {
        for (int e = 0; e < grid_size; e++)
        {
            grid[i][e] = PickWhatToPlace();
        }
    }

    int randomX1 = GenerateRandomNumber(0, grid_size);
    int randomY1 = GenerateRandomNumber(0, grid_size);
    grid[randomX1][randomY1] = 'b';

    int randomX2 = GenerateRandomNumber(0, grid_size);
    int randomY2 = GenerateRandomNumber(0, grid_size);
    grid[randomX2][randomY2] = 'H';
    marioX = randomX2;
    marioY = randomY2;

    if (current_level < max_levels)
    {
        int randomX3 = GenerateRandomNumber(0, grid_size);
        int randomX4 = GenerateRandomNumber(0, grid_size);
        grid[randomX3][randomX4] = 'w';
    }
}

/*
Name Of Function: PickWhatToPlace

Description of Value Returned: a char which is what will be placed in a specific spot on the grid

Description of Parameters: 

Description of exceptions thrown: 
*/

char Game::PickWhatToPlace()
{
    if (probability_for_coin == 20 && probability_for_nothing == 20 && probability_for_goomba == 20 && probability_for_koopatroopa == 20 && probability_for_mushroom == 20)
    {
        int probabilityNumber = GenerateRandomNumber(1, 5);
        return CheckProbabilitiesForEqualChance(probabilityNumber);
    }
    int probabilityNumber = GenerateRandomNumber(1, 100);
    SortProbabilities();
    return CheckProbabilities(probabilityNumber);
}

/*
Name Of Function: CheckProbabilitiesForEqualChancE

Description of Value Returned: A char which is what will be placed on a specific spot on the grid

Description of Parameters: probability number (int) that matches the probability with a char that will be placed in the 
incident of all equal chances for them to be plaecd

Description of exceptions thrown: 
*/

char Game::CheckProbabilitiesForEqualChance(int probabilityNumber)
{
    if (probabilityNumber == 1)
    {
        return 'c';
    }
    else if (probabilityNumber == 2)
    {
        return 'x';
    }
    else if (probabilityNumber == 3)
    {
        return 'g';
    }
    else if (probabilityNumber == 4)
    {
        return 'k';
    }
    else
    {
        return 'm';
    }
}

/*
Name Of Function: CheckProbabilities

Description of Value Returned: A char that will be placed in a specific place in the case of the probabilities are all different numbers

Description of Parameters: probability number (int) is the probability chosen and then gets checked to see where it falls under to place

Description of exceptions thrown: 
*/

char Game::CheckProbabilities(int probabilityNumber)
{
    if (probabilityNumber < probabilities[0])
    {
        return CompareProbability(probabilities[0]);
    }
    else if (probabilityNumber < probabilities[0] + probabilities[1])
    {
        return CompareProbability(probabilities[1]);
    }
    else if (probabilityNumber < probabilities[0] + probabilities[1] + probabilities[2])
    {
        return CompareProbability(probabilities[2]);
    }
    else if (probabilityNumber < probabilities[0] + probabilities[1] + probabilities[2] + probabilities[3])
    {
        return CompareProbability(probabilities[3]);
    }
    else
    {
        return CompareProbability(probabilities[4]);
    }
}

/*
Name Of Function: CompareProbability

Description of Value Returned: char that is the chosen thing that will be placed

Description of Parameters: probability (int) that checks each individual probability and matches them to the current probability to see what to place

Description of exceptions thrown: 
*/

char Game::CompareProbability(int probability)
{
    if (probability == probability_for_coin)
    {
        return 'c';
    }
    else if (probability == probability_for_koopatroopa)
    {
        return 'k';
    }
    else if (probability == probability_for_goomba)
    {
        return 'g';
    }
    else if (probability == probability_for_nothing)
    {
        return 'x';
    }
    else
    {
        return 'm';
    }
}

/*
Name Of Function: SortProbabilities

Description of Value Returned: 

Description of Parameters: 

Description of exceptions thrown: 
*/

void Game::SortProbabilities()
{
    std::sort(std::begin(probabilities), std::end(probabilities));
}

/*
Name Of Function: GenerateRandomNumber

Description of Value Returned: 

Description of Parameters: minNumber (int) which is the minimum range and maxNumber (int) which is the maximum range

Description of exceptions thrown: 
*/

int Game::GenerateRandomNumber(int minNumber, int maxNumber)
{
    int randomNum = (rand() % maxNumber) + minNumber;
    return randomNum;
}

/*
Name Of Function: CommentPosition - Debugging purposes
.
Description of Value Returned: 

Description of Parameters: std::string direction of the direction we will be going

Description of exceptions thrown: 
*/

void Game::CommentPosition(std::string direction)
{
    cout << "[";
    cout << marioX;
    cout << ",";
    cout << marioY;
    cout << "]";
    cout << direction << endl;
    CommentGrid();
}

/*
Name Of Function: CommentGrid - Debugging Purposes

Description of Value Returned: 

Description of Parameters: 

Description of exceptions thrown: 
*/

void Game::CommentGrid()
{
    int line_length = 0;
    for (int i = 0; i < grid_size; i++)
    {
        for (int e = 0; e < grid_size; e++)
        {
            if (line_length < grid_size - 1)
            {
                cout << "[";
                cout << grid[i][e];
                cout << "]";
                line_length++;
            }
            else
            {
                cout << "[";
                cout << grid[i][e];
                cout << "]" << endl;
                line_length = 0;
            }
        }
    }
}

/*
Name Of Function: OutputStringToFile

Description of Value Returned: 

Description of Parameters: std::string that will be outputted to file

Description of exceptions thrown: 
*/

void Game::OutputStringToFile(std::string string){
    std::ofstream file;
    file.open(outputFileName, std::ios_base::app);
    file << string << endl;
    file.close();
}

/*
Name Of Function: OutputIntToFile

Description of Value Returned: 

Description of Parameters: int integer that will output an integer to the output fille

Description of exceptions thrown: 
*/

void Game::OutputIntToFile(int integer){
    std::ofstream file;
    file.open(outputFileName, std::ios_base::app);
    file << integer << endl;
    file.close();
}
