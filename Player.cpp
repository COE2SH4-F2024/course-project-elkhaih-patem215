#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPosList = new objPosArrayList();
    playerPosList -> insertHead(objPos(15, 7,'$'));

}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPosList() const
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
        // PPA3 input processing logic 

        char input = mainGameMechsRef -> getInput();

        switch(input)
        {                      
            case 27:  // exit if ESC key pressed
                mainGameMechsRef -> setExitTrue();
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

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    // int BoardSizeX = mainGameMechsRef -> getBoardSizeX();
    // int BoardSizeY = mainGameMechsRef -> getBoardSizeY();

    // switch (myDir)
    // {
    //     case UP:
    //         playerPos.pos -> y--;
            
    //         if(playerPos.pos -> y < 1)
    //         {
    //             playerPos.pos -> y = 13; //wrap around, up to down
    //         }
    //         break;

    //     case DOWN:
    //         playerPos.pos -> y++;
    //         if(playerPos.pos -> y> 13)
    //         {
    //             playerPos.pos -> y = 1; //wrap around, down to up
    //         }
    //         break;

    //     case LEFT:
    //         playerPos.pos -> x--;
    //         if(playerPos.pos -> x < 1)
    //         {
    //             playerPos.pos -> x = 28; //wrap around, left to right
    //         }
    //         break;

    //     case RIGHT:
    //         playerPos.pos -> x++;
    //         if(playerPos.pos -> x > 28)
    //         {
    //             playerPos.pos -> x = 1; //wrap around, right to left
    //         }
    //         break;

    //     default:
    //         break;
    // }

    objPos head = playerPosList->getHeadElement();
    int newX = head.pos->x, newY = head.pos->y;

    switch (myDir) 
    {
        case UP: newY--; break;
        case DOWN: newY++; break;
        case LEFT: newX--; break;
        case RIGHT: newX++; break;
        default: return; 
    }

    if (newX < 1) newX = mainGameMechsRef->getBoardSizeX() - 2;
    if (newX >= mainGameMechsRef->getBoardSizeX() - 1) newX = 1;
    if (newY < 1) newY = mainGameMechsRef->getBoardSizeY() - 2;
    if (newY >= mainGameMechsRef->getBoardSizeY() - 1) newY = 1;

    playerPosList->insertHead(objPos(newX, newY, '$')); // Add new head
    checkfoodcoll(); 
    checkselfcoll(); // Check for self-collision

    // Only remove the tail if the snake didn't grow
    if (playerPosList->getSize() > 1) 
    {
        playerPosList->removeTail();
    }
    
}

// More methods to be added

void Player::checkselfcoll() {
    objPos head = playerPosList->getHeadElement();

    for (int i = 1; i < playerPosList->getSize(); ++i) {
        objPos bodySegment = playerPosList->getElement(i);
        if (head.isPosEqual(&bodySegment)) {
            mainGameMechsRef->setLoseFlag();
            mainGameMechsRef->setExitTrue();
            break;
        }
    }
}

void Player::checkfoodcoll() {
    objPos head = playerPosList->getHeadElement(); // Get the head of the snake
    objPos food = mainGameMechsRef->getFoodPos();  // Get the food's position

    // Check if the snake's head is at the same position as the food
    if (head.isPosEqual(&food)) {
        mainGameMechsRef->incrementScore(); // Increase score
        mainGameMechsRef->generateFood(*playerPosList); // Generate a new food position
        // Do not remove the tail (this is what grows the snake)
    } else {
        // If no food was eaten, remove the tail to maintain snake length
        if (playerPosList->getSize() > 1) {
            playerPosList->removeTail();
        }
    }
}