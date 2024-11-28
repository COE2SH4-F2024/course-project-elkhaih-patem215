#include "GameMechs.h"

GameMechs::GameMechs()
{
    
}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    input = 0;
    specialFoodActive = false;

}

void GameMechs::generateFood(const objPosArrayList& snakeBody) {
    srand(time(0)); // Seed random number generator
    int newX, newY;
    bool posValid = false;

    while (!posValid) {
        // Generate random position
        newX = rand() % (boardSizeX - 2) + 1;
        newY = rand() % (boardSizeY - 2) + 1;
        posValid = true;

        // Check for overlap with snake body
        for (int i = 0; i < snakeBody.getSize(); ++i) {
            if (snakeBody.getElement(i).pos->x == newX &&
                snakeBody.getElement(i).pos->y == newY) {
                posValid = false;
                break;
            }
        }
    }

    // Set the new food position
    food.setObjPos(newX, newY, '@');
}

void GameMechs::generateFoods(const objPosArrayList& snakeBody) {
    srand(time(0)); // Seed random number generator
    int newX, newY;
    bool posValid;

    // Generate regular foods
    for (int i = 0; i < 2; ++i) {
        do {
            posValid = true;
            newX = rand() % (boardSizeX - 2) + 1; // Ensure within boundaries
            newY = rand() % (boardSizeY - 2) + 1;

            // Check overlap with snake
            for (int j = 0; j < snakeBody.getSize(); ++j) {
                if (snakeBody.getElement(j).pos->x == newX &&
                    snakeBody.getElement(j).pos->y == newY) {
                    posValid = false;
                    break;
                }
            }

            // Ensure no overlap with previously placed foods
            for (int j = 0; j < i; ++j) {
                if (regularFoods[j].pos->x == newX && regularFoods[j].pos->y == newY) {
                    posValid = false;
                    break;
                }
            }
        } while (!posValid);

        regularFoods[i].setObjPos(newX, newY, '*'); // Regular food symbol
    }

    // Generate special food
    if (!specialFoodActive) {
        do {
            posValid = true;
            newX = rand() % (boardSizeX - 2) + 1;
            newY = rand() % (boardSizeY - 2) + 1;

            // Check overlap with snake
            for (int j = 0; j < snakeBody.getSize(); ++j) {
                if (snakeBody.getElement(j).pos->x == newX &&
                    snakeBody.getElement(j).pos->y == newY) {
                    posValid = false;
                    break;
                }
            }

            // Ensure no overlap with regular foods
            for (int j = 0; j < 2; ++j) {
                if (regularFoods[j].pos->x == newX && regularFoods[j].pos->y == newY) {
                    posValid = false;
                    break;
                }
            }
        } while (!posValid);

        specialFood.setObjPos(newX, newY, '@'); // Special food symbol
        specialFoodActive = true;
    }
}

objPos GameMechs::getRegularFood(int index) const 
{
    return regularFoods[index];
}
objPos GameMechs::getSpecialFood() const 
{
    return specialFood;
}

bool GameMechs::isSpecialFoodActive() const 
{
    return specialFoodActive;
}

void GameMechs::setSpecialFoodActive(bool isActive) 
{
    specialFoodActive = isActive;
}



objPos GameMechs::getFoodPos() const
{
    return food;
}
// do you need a destructor?
GameMechs::~GameMechs()
{
    
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore(int points)
{
    score += points;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

// More methods should be added here