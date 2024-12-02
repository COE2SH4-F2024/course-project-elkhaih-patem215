#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"          // Includes the objPos class - for managing object positions
#include "objPosArrayList.h" // Includes the objPosArrayList class-likely for snake body management

using namespace std;

// Define the GameMechs class, which manages the mechanics of the game
class GameMechs
{
    private:
        char input;     // Stores the most recent player input
        bool exitFlag;  // Flag to indicate if the game should exit
        bool loseFlag;  // Flag to indicate if the player has lost the game
        int score;      // Player's current score

        int boardSizeX; // Width of the game board
        int boardSizeY; // Height of the game board

        objPos food;    // Position of the current food

        //Bonus// Bonus feature: Managing multiple food items
        objPos regularFoods[2];  // Two regular foods
        objPos specialFood;      // One special food
        bool specialFoodActive;  // Is the special food active?

    public:
        // Constructors and Destructor
        GameMechs();
        GameMechs(int boardX, int boardY);
        ~GameMechs(); // is this one needed at all? Why or why not?
        
        // Game control methods
        bool getExitFlagStatus() const; 
        void setExitTrue();
        bool getLoseFlagStatus() const;
        void setLoseFlag();

         // Input handling methods
        char getInput() const;
        void setInput(char this_input);
        void clearInput();

        // Board dimension methods
        int getBoardSizeX() const;
        int getBoardSizeY() const;

        // Scoring methods
        int getScore() const;
        void incrementScore(int points = 1);
        
        // Food generation and retrieval methods
        void generateFood(const objPosArrayList& snakeBody);
        objPos getFoodPos() const;

        // Bonus methods for handling multiple food items
        void generateFoods(const objPosArrayList& snakeBody); // Generate all foods
        objPos getRegularFood(int index) const;              // Get regular food by index
        objPos getSpecialFood() const;                       // Get special food
        bool isSpecialFoodActive() const;                    // Check if special food is active
        void setSpecialFoodActive(bool isActive);
};

#endif