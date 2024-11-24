#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.setObjPos(15, 7,'$');

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

            mainGameMechsRef->clearInput();  
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
            playerPos.pos -> y--;
            
            if(playerPos.pos -> y < 1)
            {
                playerPos.pos -> y = 13; //wrap around, up to down
            }
            break;

        case DOWN:
            playerPos.pos -> y++;
            if(playerPos.pos -> y> 13)
            {
                playerPos.pos -> y = 1; //wrap around, down to up
            }
            break;

        case LEFT:
            playerPos.pos -> x--;
            if(playerPos.pos -> x < 1)
            {
                playerPos.pos -> x = 28; //wrap around, left to right
            }
            break;

        case RIGHT:
            playerPos.pos -> x++;
            if(playerPos.pos -> x > 28)
            {
                playerPos.pos -> x = 1; //wrap around, right to left
            }
            break;

        default:
            break;
    }

}

// More methods to be added