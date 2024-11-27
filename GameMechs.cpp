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

}

// void GameMechs::generateFood(const objPos& blockOff)
// {
//     srand(time(0));
//     int newX, newY;
//     bool posValid = false;

//     while(!posValid)
//     {
//         newX = rand() % boardSizeX;
//         newY = rand() % boardSizeY;

//         if (newX != blockOff.pos->x || newY != blockOff.pos->y)
//         {
//             posValid = true;
//         }
//     }

//     food.setObjPos(newX, newY, '*');
// }

void GameMechs::generateFood(const objPosArrayList& snakeBody) {
    srand(time(0)); // Seed random number generator
    int newX, newY;
    bool posValid = false;

    // Generate food position that does not overlap with the snake's body
    while (!posValid) {
        newX = rand() % boardSizeX;
        newY = rand() % boardSizeY;
        posValid = true;

        // Check if the new position overlaps with any part of the snake
        for (int i = 0; i < snakeBody.getSize(); ++i) {
            if (snakeBody.getElement(i).pos->x == newX &&
                snakeBody.getElement(i).pos->y == newY) {
                posValid = false;
                break;
            }
        }
    }

    // Set the new food position and symbol
    food.setObjPos(newX, newY, '*');
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

void GameMechs::incrementScore()
{
    score++;
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