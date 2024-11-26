#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

#include "Player.h"
#include "GameMechs.h"

using namespace std;

#define DELAY_CONST 100000

bool exitFlag;
const int board_width = 30;
const int board_height = 15; 
const int num_obj = 3; // test with 3 objs first


objPos objects[num_obj]; //array to hold objPos objects

GameMechs* gameMechanics;
Player* player;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(exitFlag == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    exitFlag = false;

    gameMechanics = new GameMechs(board_width, board_height);
    player = new Player(gameMechanics);

    gameMechanics->generateFood(*player->getPlayerPosList());


}

void GetInput(void)
{
    
    if(MacUILib_hasChar())
    {
        char input = MacUILib_getChar();
        gameMechanics->setInput(input);
    }

}

void RunLogic(void)
{
    player -> updatePlayerDir();
    player -> movePlayer();

    if(gameMechanics->getExitFlagStatus())
    {
        exitFlag = true;
    }



}

void DrawScreen(void)
{
    MacUILib_clearScreen();    

    //draw the game board
    for(int y = 0; y < board_height; ++y)
    {
        for(int x = 0; x < board_width; ++x)
        {

            if(x==0 || x == board_width - 1 || y == 0 || y == board_height - 1)
            {
                std::cout << '#'; //border
                continue;
            }

            bool printed = false;

            // Draw the snake
            objPosArrayList* snakeBody = player->getPlayerPosList();
            for (int i = 0; i < snakeBody->getSize(); ++i) {
                objPos segment = snakeBody->getElement(i);
                if (segment.pos->x == x && segment.pos->y == y) {
                    std::cout << segment.symbol;
                    printed = true;
                    break;
                }
            }

            // Draw the food
           objPos food = gameMechanics->getFoodPos();
            if (!printed && food.pos != nullptr && food.pos->x == x && food.pos->y == y) {
                std::cout << food.symbol; // Food symbol
                printed = true;
            }

            // Draw empty spaces
            if (!printed) {
                std::cout << ' ';
            }
        }
        std::cout << '\n'; // Move to the next line after each row
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    MacUILib_uninit();
    
    delete player;
    delete gameMechanics;
}

