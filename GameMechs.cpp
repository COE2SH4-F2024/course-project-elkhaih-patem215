#include "GameMechs.h"

GameMechs::GameMechs()
{
    // Empty constructor body for default initialization
}

//Initialize game mechanics with board dimensions
GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;            // Set board width
    boardSizeY = boardY;            // Set board height
    exitFlag = false;               // Game exit flag, initially false
    loseFlag = false;               // Game lose flag, initially false
    score = 0;                      // Initial score is 0
    input = 0;                      // No input at the start
    specialFoodActive = false;      // Special food is not active initially

}

// Generate a single piece of food on the board
void GameMechs::generateFood(const objPosArrayList& snakeBody) {
    srand(time(0)); // Seed random number generator
    int newX, newY; // Coordinates for the new food
    bool posValid = false; // Flag to check if position is valid

    while (!posValid) {
        // Generate random position within board boundaries
        newX = rand() % (boardSizeX - 2) + 1;
        newY = rand() % (boardSizeY - 2) + 1;
        posValid = true;

        // Check for overlap with snake body
        for (int i = 0; i < snakeBody.getSize(); ++i) {
            if (snakeBody.getElement(i).pos->x == newX &&
                snakeBody.getElement(i).pos->y == newY) {
                posValid = false; // Position is invalid
                break;
            }
        }
    }

    // Set the new food position and symbol
    food.setObjPos(newX, newY, '@');
}

// Generate multiple foods regular and special on the board
void GameMechs::generateFoods(const objPosArrayList& snakeBody) {
    srand(time(0)); // Seed random number generator
    int newX, newY;
    bool posValid;

    // Generate 2 regular foods
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

        // Set regular food position and symbol
        regularFoods[i].setObjPos(newX, newY, '*'); // Regular food symbol
    }

    // Generate special food if not already active
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
        
        // Set special food position and symbol
        specialFood.setObjPos(newX, newY, '@'); // Special food symbol
        specialFoodActive = true; // Activate special food
    }
}

// Retrieve the position of a specific regular food
objPos GameMechs::getRegularFood(int index) const 
{
    return regularFoods[index];
}
// Retrieve the position of the special food
objPos GameMechs::getSpecialFood() const 
{
    return specialFood;
}
// Check if the special food is currently active
bool GameMechs::isSpecialFoodActive() const 
{
    return specialFoodActive;
}
// Set the activation status of the special food
void GameMechs::setSpecialFoodActive(bool isActive) 
{
    specialFoodActive = isActive;
}

// Retrieve the position of the general food
objPos GameMechs::getFoodPos() const
{
    return food;
}

// Destructor: No specific cleanup required
GameMechs::~GameMechs()
{
    
}
// Get the status of the game exit flag
bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}
// Get the status of the game lose flag
bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
// Get the latest input
char GameMechs::getInput() const
{
    return input;
}
// Get the current score
int GameMechs::getScore() const
{
    return score;
}
// Increment the score by a specified amount
void GameMechs::incrementScore(int points)
{
    score += points;
}
// Get the width of the board
int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}
// Get the height of the board
int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}
// Set the exit flag to true
void GameMechs::setExitTrue()
{
    exitFlag = true;
}
// Set the lose flag to true
void GameMechs::setLoseFlag()
{
    loseFlag = true;
}
// Set the current input
void GameMechs::setInput(char this_input)
{
    input = this_input;
}
// Clear the current input
void GameMechs::clearInput()
{
    input = 0;
}
