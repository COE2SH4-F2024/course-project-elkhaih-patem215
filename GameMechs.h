#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class GameMechs
{
    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        int score;

        int boardSizeX;
        int boardSizeY;

        objPos food;

        //Bonus
        objPos regularFoods[2];  // Two regular foods
        objPos specialFood;      // One special food
        bool specialFoodActive;  // Is the special food active?

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        ~GameMechs(); // is this one needed at all? Why or why not?
        
        bool getExitFlagStatus() const; 
        void setExitTrue();
        bool getLoseFlagStatus() const;
        void setLoseFlag();

        char getInput() const;
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX() const;
        int getBoardSizeY() const;
        
        int getScore() const;
        void incrementScore(int points = 1);
        
        // More methods should be added here

        void generateFood(const objPosArrayList& snakeBody);
        objPos getFoodPos() const;

        //Bonus
        void generateFoods(const objPosArrayList& snakeBody); // Generate all foods
        objPos getRegularFood(int index) const;              // Get regular food by index
        objPos getSpecialFood() const;                       // Get special food
        bool isSpecialFoodActive() const;                    // Check if special food is active
        void setSpecialFoodActive(bool isActive);
};

#endif