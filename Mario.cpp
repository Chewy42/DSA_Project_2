/*
Name: Matt Favela
Student ID #: 2390407
Email: mfavela@chapman.edu
Course Number and Section: CPSC350-03
Assignment: PA2

Brief Overview:
This class creates the Mario along with all its stats, accessors, and mutators

High Level Decisions Used:
I tried to simplify the file as much as possible so its easy to read.
*/

#include "Mario.h"

using namespace std;

/*
Name Of Function: Mario class constructor

Description of Value Returned: None

Description of Parameters: None

Description of exceptions thrown: None
*/
Mario::Mario(){
    number_of_lives = 0;
    number_of_coins = 0;
    current_power_level = 0;
}

/*
Name Of Function: Mario class overloaded constructor

Description of Value Returned: None

Description of Parameters: number of marios starting lives

Description of exceptions thrown: None
*/

Mario::Mario(int number_of_lives){
    this->number_of_lives = number_of_lives;
    number_of_coins = 0;
    current_power_level = 0;
}

/*
Name Of Function: Mario class destructor

Description of Value Returned: None

Description of Parameters: None

Description of exceptions thrown: None
*/
Mario::~Mario(){
    
}

/*
Name Of Function: get number of lives

Description of Value Returned: integer of the number of lives

Description of Parameters: None

Description of exceptions thrown: None
*/

int Mario::getNumberOfLives(){
    return number_of_lives;
}

/*
Name Of Function: get number of coins

Description of Value Returned: integer of number of coins

Description of Parameters: None

Description of exceptions thrown: None
*/

int Mario::getNumberOfCoins(){
    return number_of_coins;
}

/*
Name Of Function: get current power level

Description of Value Returned: integer of current power level

Description of Parameters: None

Description of exceptions thrown: None
*/

int Mario::getCurrentPowerLevel(){
    return current_power_level;
}

/*
Name Of Function: set number of lives

Description of Value Returned: None

Description of Parameters: integer of lives to set

Description of exceptions thrown: None
*/

void Mario::setNumberOfLives(int lives_amount){
    number_of_lives = lives_amount;
}

/*
Name Of Function: set number of coins

Description of Value Returned: None

Description of Parameters: integer of coins to set

Description of exceptions thrown: None
*/

void Mario::setNumberOfCoins(int coins){
    number_of_coins = coins;
}

/*
Name Of Function: set current power level

Description of Value Returned: None

Description of Parameters: integer of power level to set

Description of exceptions thrown: None
*/

void Mario::setCurrentPowerLevel(int power_level_amount){
    current_power_level = power_level_amount;
}

/*
Name Of Function: increase power level

Description of Value Returned: None

Description of Parameters: integer of amount to increment power level

Description of exceptions thrown: None
*/

void Mario::IncreasePowerLevel(int incrementAmount){
    if(current_power_level == 2){
        return;
    }else{
        current_power_level++;
    }
}

/*
Name Of Function: decrease power level

Description of Value Returned: None

Description of Parameters: integer of amount to decrement power level

Description of exceptions thrown: None
*/

void Mario::DecreasePowerLevel(int decrementAmount){
    current_power_level--;
}

/*
Name Of Function: increment coins

Description of Value Returned: None

Description of Parameters: 

Description of exceptions thrown: None
*/

void Mario::IncrementCoins(){
    number_of_coins++;
}

/*
Name Of Function: consume mushroom

Description of Value Returned: None

Description of Parameters: 

Description of exceptions thrown: None
*/

void Mario::ConsumeMushroom(){
    IncreasePowerLevel(1);
}

/*
Name Of Function: lose power level

Description of Value Returned: None

Description of Parameters:

Description of exceptions thrown: None
*/

void Mario::LosePowerLevel(){
    DecreasePowerLevel(1);
}