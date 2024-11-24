#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.setObjPos(5,5, '$');

}


Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
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
        }         
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    int BoardSizeX = mainGameMechsRef -> getBoardSizeX();
    int BoardSizeY = mainGameMechsRef -> getBoardSizeY();

    switch (myDir)
    {
        case UP:
            playerPos.pos -> y = (playerPos.pos->y - 1 + BoardSizeY) % BoardSizeY;
            break;

        case DOWN:
            playerPos.pos -> y = (playerPos.pos->y + 1) % BoardSizeY;
            break;

        case LEFT:
            playerPos.pos -> x = (playerPos.pos->x - 1 + BoardSizeX) % BoardSizeX;
            break;

        case RIGHT:
            playerPos.pos -> x = (playerPos.pos->x + 1) % BoardSizeX;
            break;

        default:
            break;
    }
}

// More methods to be added