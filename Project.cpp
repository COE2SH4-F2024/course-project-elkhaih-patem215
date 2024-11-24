#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

using namespace std;

#define DELAY_CONST 100000

bool exitFlag;
const int board_width = 30;
const int board_height = 15; 
const int num_obj = 3; // test with 3 objs first
char input;

objPos objects[num_obj]; //array to hold objPos objects

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

    objects[0].setObjPos(5, 5, 'A');
    objects[1].setObjPos(10, 10, 'B');
    objects[2].setObjPos(15, 7, 'C');
}

void GetInput(void)
{
    
    if(MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }

}

void RunLogic(void)
{
     if (input == 27)
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
            bool printed = false;

            //check if objPos exists at this position 
            for (int i = 0; i < num_obj; ++i)
            {
                if (objects[i].pos->x == x && objects[i].pos->y == y)
                {
                    cout << objects[i].symbol;
                    printed = true;
                    break;
                }
            }

            //draw border or empty space
            if(!printed)
            {
                if (x == 0 || x == board_width - 1 || y == 0 || y == board_height -1)
                {
                    cout << '#'; //boarder
                }

                else
                {
                    cout << " ";
                }
            }
        }

        cout << '\n';
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
}
