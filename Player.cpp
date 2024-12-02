#include "Player.h"


Player::Player(GameMechs* thisGMRef) // Constructor: Initializes the player and sets up the starting position
{
    mainGameMechsRef = thisGMRef; // Store reference to the main game mechanics
    myDir = STOP;  // Set initial direction to STOP


    // more actions to be included
    playerPosList = new objPosArrayList(); // Initialize the player's position list
    playerPosList->insertHead(objPos(15, 7, '$')); // Add the initial head position
}



Player::~Player() // Destructor: Cleans up the player's resources
{
    delete playerPosList; // Deallocate the snake body list
    playerPosList = nullptr;
}

objPosArrayList* Player::getPlayerPosList() const  // Returns a reference to the player's position list
{
    
    return playerPosList;
}

void Player::updatePlayerDir() // Updates the player's direction based on user input
{
        // PPA3 input processing logic 

        char input = mainGameMechsRef -> getInput(); // Retrieve input from game mechanics

        switch(input)
        {                      
            case 27:  // exit if ESC key pressed
                mainGameMechsRef -> setExitTrue();
                quit = 1;
                break;

            //w for moving up
            case 'W':
            case 'w':
                if(myDir == LEFT || myDir == RIGHT || myDir == STOP)
                    myDir = UP;
                break;

            //s for moving down
            case 'S':
            case 's':
                if(myDir == LEFT || myDir == RIGHT || myDir == STOP)
                    myDir = DOWN;
                break;

            //d for moving right
            case 'D':
            case 'd':
                if(myDir == UP || myDir == DOWN || myDir == STOP)
                    myDir = RIGHT;
                break;

            //a for moving left
            case 'A':
            case 'a':
                if(myDir == UP || myDir == DOWN || myDir == STOP)
                    myDir = LEFT;
                break;

            default:
                myDir = STOP;
                break;

            mainGameMechsRef->clearInput();  
        }    

}

void Player::movePlayer() // Moves the player in the current direction, handles collisions, and manages wrap-around
{
    objPos headCur = playerPosList->getHeadElement(); // Get the current head position
    objPos headNew = headCur; // Create a new position based on the current head

    // Update the new head position based on the direction
    switch (myDir) {
        case UP:    headNew.pos->y--; break;
        case DOWN:  headNew.pos->y++; break;
        case LEFT:  headNew.pos->x--; break;
        case RIGHT: headNew.pos->x++; break;
        default:    return; // No movement
    }

     // Wrap around the board
    if (headNew.pos->x < 1) headNew.pos->x = mainGameMechsRef->getBoardSizeX() - 2;
    if (headNew.pos->x >= mainGameMechsRef->getBoardSizeX() - 1) headNew.pos->x = 1;
    if (headNew.pos->y < 1) headNew.pos->y = mainGameMechsRef->getBoardSizeY() - 2;
    if (headNew.pos->y >= mainGameMechsRef->getBoardSizeY() - 1) headNew.pos->y = 1;

    // Check for collisions
    checkfoodcoll(headNew);       // Handle regular food collision
    checkSpecialfoodcoll(headNew); // Handle special food collision
    checkselfcoll(headNew);       // Handle self-collision (end game if necessary)
}
// More methods to be added

void Player::checkselfcoll(const objPos& headNew)  // Checks if the player collides with its own body 
{
    
    for (int i = 1; i < playerPosList->getSize(); ++i) { 
        objPos bodyPart = playerPosList->getElement(i);
        if (headNew.pos->x == bodyPart.pos->x && headNew.pos->y == bodyPart.pos->y) {
            mainGameMechsRef->setLoseFlag();
            mainGameMechsRef->setExitTrue();
            break;
        }
    }
}

void Player::checkfoodcoll(const objPos& headNew) // Checks if the player collides with regular food
{
    // Check collision with regular foods
    for (int i = 0; i < 2; ++i) {
        objPos food = mainGameMechsRef->getRegularFood(i);
        if (headNew.pos->x == food.pos->x && headNew.pos->y == food.pos->y) {
            // Add new head without removing the tail to grow the snake
            playerPosList->insertHead(headNew);

            // Increment score
            mainGameMechsRef->incrementScore();

            // Regenerate all foods
            mainGameMechsRef->generateFoods(*playerPosList);
            return; // Exit after handling collision
        }
    }

    // If no collision with food, perform regular movement
    playerPosList->insertHead(headNew);
    playerPosList->removeTail(); // Only remove the tail if no food is eaten
}


void Player::handleMovement(const objPos& headNew) // Handles movement and manages the snake's body
{
    playerPosList->insertHead(headNew);

    // Remove the tail only if food was not consumed
    if (playerPosList->getSize() > 1) 
    {
        playerPosList->removeTail();
    }
}



void Player::checkSpecialfoodcoll(const objPos& headNew) // Checks if the player collides with special food 
{
    // Check if special food is active
    if (mainGameMechsRef->isSpecialFoodActive()) {
        objPos specialFood = mainGameMechsRef->getSpecialFood();

        // If the snake's head collides with the special food
        if (headNew.pos->x == specialFood.pos->x && headNew.pos->y == specialFood.pos->y) {
            mainGameMechsRef->incrementScore(20); // Add 20 points to the score

            // Deactivate the special food and regenerate all foods
            mainGameMechsRef->setSpecialFoodActive(false); 
            mainGameMechsRef->generateFoods(*playerPosList); 
        }
    }
}