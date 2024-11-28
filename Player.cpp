#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(objPos(15, 7, '$'));

}


Player::~Player() 
{
    delete playerPosList; // Deallocate the snake body list
    playerPosList = nullptr;
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

void Player::movePlayer() {
    objPos headCur = playerPosList->getHeadElement();
    objPos headNew = headCur;

    // Determine the new head position based on direction
    switch (myDir) {
        case UP:    headNew.pos->y--; break;
        case DOWN:  headNew.pos->y++; break;
        case LEFT:  headNew.pos->x--; break;
        case RIGHT: headNew.pos->x++; break;
        default:    return; // No movement
    }

    // Handle board wrap-around
    if (headNew.pos->x < 1) headNew.pos->x = mainGameMechsRef->getBoardSizeX() - 2;
    if (headNew.pos->x >= mainGameMechsRef->getBoardSizeX() - 1) headNew.pos->x = 1;
    if (headNew.pos->y < 1) headNew.pos->y = mainGameMechsRef->getBoardSizeY() - 2;
    if (headNew.pos->y >= mainGameMechsRef->getBoardSizeY() - 1) headNew.pos->y = 1;

    // Check collisions
    checkfoodcoll(headNew); // Handle food collision and growth
    checkselfcoll(headNew); // Handle self-collision (game over)
}
// More methods to be added

void Player::checkselfcoll(const objPos& headNew) {
    // Check if the new head position collides with any part of the snake body
    for (int i = 1; i < playerPosList->getSize(); ++i) { // Skip the head (index 0)
        objPos bodyPart = playerPosList->getElement(i);
        if (headNew.pos->x == bodyPart.pos->x && headNew.pos->y == bodyPart.pos->y) {
            mainGameMechsRef->setLoseFlag();
            mainGameMechsRef->setExitTrue();
            break;
        }
    }
}

void Player::checkfoodcoll(const objPos& headNew) {
    // Check if the head collides with food
    objPos foodPos = mainGameMechsRef->getFoodPos();
    if (headNew.pos->x == foodPos.pos->x && headNew.pos->y == foodPos.pos->y) {
        // Add new head but do not remove tail (snake grows)
        playerPosList->insertHead(headNew);

        // Increment score and generate new food
        mainGameMechsRef->incrementScore();
        mainGameMechsRef->generateFood(*playerPosList);
    } else {
        // Regular movement (add head, remove tail)
        playerPosList->insertHead(headNew);
        playerPosList->removeTail();
    }
}

void Player::handleMovement(const objPos& headNew) 
{
    playerPosList->insertHead(headNew);

    // Remove the tail only if food was not consumed
    if (playerPosList->getSize() > 1) {
        playerPosList->removeTail();
    }
}